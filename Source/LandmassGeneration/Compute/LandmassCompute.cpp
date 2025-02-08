#include "LandmassCompute.h"
#include "CoreMinimal.h"
#include "LandmassGeneration/Shaders/LandmassComputeShader.h"

#include "RenderGraphUtils.h"           // RDG utility functions
#include "RenderGraphResources.h"       // RDG buffer and texture handling
#include "RenderGraphBuilder.h"         // Required for FRDGBuilder
#include "ShaderParameterUtils.h"       // Required for shader parameters
#include "RHIResources.h"               // Handles RHI buffers and resources
#include <LandmassGeneration/Manager/LandmassManager.h>

void FMyComputeShaderWrapper::Dispatch(uint32 SizeOfElement, uint32 NumElements)
{
	ENQUEUE_RENDER_COMMAND(MyRenderCommand)(
		[this, SizeOfElement, NumElements](FRHICommandListImmediate& RHICmdList)
		{
			// Get the global shader map
			TShaderMapRef<FMyComputeShader> MyComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

			// Use RDG for GPU resource management
			FRDGBuilder GraphBuilder(RHICmdList);

			// Create Triangle Table SRV
			FRDGBufferSRVRef TriangleTableBufferSRV = CreateTriangleTableSRV(GraphBuilder);

			// Create GPU Buffer
			FRDGBufferRef OutputBuffer = CreateOutputBuffer(GraphBuilder, SizeOfElement, NumElements);
			// Create an UAV Buffer to enable RW on GPU Buffer
			FRDGBufferUAVRef OutputBufferUAV = CreateUAVBuffer(GraphBuilder, OutputBuffer);
			
			// Allocate parameters
			FMyComputeShader::FParameters* PassParameters = GraphBuilder.AllocParameters<FMyComputeShader::FParameters>();
			PassParameters->OutputBufferUAV = OutputBufferUAV;
			PassParameters->TriangleTableBufferSRV = TriangleTableBufferSRV;

			// Dispatch the compute shader using FComputeShaderUtils
			// Number of Thread Groups
			FIntVector NumOfThreadGroups(NumElements, 1, 1);

			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("ComputeShaderPass"),
				MyComputeShader,
				PassParameters,
				NumOfThreadGroups
			);

			FRHIGPUBufferReadback* ReadbackBuffer = new FRHIGPUBufferReadback(TEXT("ComputeReadback"));
			AddEnqueueCopyPass(GraphBuilder, ReadbackBuffer, OutputBuffer, SizeOfElement * NumElements); // Copy (n) bytes (uint32)

			// Execute the RDG Graph
			GraphBuilder.Execute();

			CheckReadbackBuffer(ReadbackBuffer, SizeOfElement, NumElements);
		});
}

// Create the buffer to hold data 
FRDGBufferRef FMyComputeShaderWrapper::CreateOutputBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements)
{
	return GraphBuilder.CreateBuffer(
		FRDGBufferDesc::CreateStructuredDesc(SizeOfElement, NumOfElements),
		TEXT("OutputBuffer")
	);
}
// Create the UAV on the buffer to enable read/write capabilities
FRDGBufferUAVRef FMyComputeShaderWrapper::CreateUAVBuffer(FRDGBuilder& GraphBuilder, const FRDGBufferRef& OutputBuffer)
{
	return GraphBuilder.CreateUAV(OutputBuffer, PF_R32_UINT);
}

FRDGBufferSRVRef FMyComputeShaderWrapper::CreateTriangleTableSRV(FRDGBuilder& GraphBuilder)
{
	// Flatten TriangleTable
	TArray<int32> FlatTriangleTable = GetFlatTriangleArray();
	// Upload Triangle Table
	FRDGBufferRef TriangleTableBuffer = UploadBuffer(GraphBuilder, FlatTriangleTable, FString("Triangle Table"));
	// Create Triangle Table SRV
	return GraphBuilder.CreateSRV(TriangleTableBuffer);
}

// Upload Buffer data to GPU
FRDGBufferRef FMyComputeShaderWrapper::UploadBuffer(FRDGBuilder& GraphBuilder, TArray<int32>& Table ,const FString& Name)
{
	int32 NumOfElements = Table.Num();

	FRDGBufferRef TableBuffer = GraphBuilder.CreateBuffer(
		FRDGBufferDesc::CreateStructuredDesc(sizeof(int32), NumOfElements),
		*Name
	);

	GraphBuilder.QueueBufferUpload(TableBuffer, Table.GetData(), NumOfElements * 4);
	return TableBuffer;
}

void FMyComputeShaderWrapper::CheckReadbackBuffer(FRHIGPUBufferReadback* ReadbackBuffer, const uint32& ElementSize, const uint32& TotalElements)
{
	uint32 TotalBufferSize = ElementSize * TotalElements;
	AsyncTask(ENamedThreads::ActualRenderingThread, [this, ReadbackBuffer, TotalElements, ElementSize ,TotalBufferSize]()
		{
			if (ReadbackBuffer->IsReady())
			{
				int32* Data = (int32*)ReadbackBuffer->Lock(TotalBufferSize);
				AsyncTask(ENamedThreads::GameThread, [Data, TotalElements]()
					{
						for (uint32 x = 0; x < TotalElements; x++)
						{
							UE_LOG(LogTemp, Warning, TEXT("Data: %d"), Data[x]);
						}
					});
				ReadbackBuffer->Unlock();
				delete ReadbackBuffer;
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [this, ReadbackBuffer, ElementSize, TotalElements]()
					{
						UE_LOG(LogTemp, Warning, TEXT("Buffer readback not ready...retrying..."));
						FTimerHandle TimerHandle;
						GWorld->GetTimerManager().SetTimer(
							TimerHandle,
							[this, ReadbackBuffer, ElementSize, TotalElements]()
							{
								CheckReadbackBuffer(ReadbackBuffer, ElementSize, TotalElements);
							},
							0.05f, // Retry delay in seconds
							false // Do not loop, just retry once
						);
					});
			}
		});
}

TArray<int32> FMyComputeShaderWrapper::GetFlatTriangleArray()
{
	TArray<int32> FlattenedArray;
	for (const TArray<int32>& Row : ULandmassManager::Get()->GetTriangulationTable())
	{
		FlattenedArray.Append(Row);
	}
	return FlattenedArray;
}