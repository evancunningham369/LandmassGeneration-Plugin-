#include "LandmassCompute.h"
#include "CoreMinimal.h"
#include "LandmassGeneration/Shaders/LandmassComputeShader.h"

#include "RenderGraphUtils.h"           // RDG utility functions
#include "RenderGraphResources.h"       // RDG buffer and texture handling
#include "RenderGraphBuilder.h"         // Required for FRDGBuilder
#include "ShaderParameterUtils.h"       // Required for shader parameters
#include "RHIResources.h"               // Handles RHI buffers and resources
#include <LandmassGeneration/Manager/LandmassManager.h>
#include "ComputeShaderReadback.h"

void FMyComputeShaderWrapper::Dispatch(UWorld* World, uint32 NumVertices, const TArray<float>& DensityData)
{
	//UE_LOG(LogTemp, Warning, TEXT("Num Vertices: %d"), NumVertices)
	//UE_LOG(LogTemp, Warning, TEXT("Num Density: %d"), DensityData.Num())
	ENQUEUE_RENDER_COMMAND(MyRenderCommand)(
		[World, this, NumVertices, DensityData](FRHICommandListImmediate& RHICmdList)
		{
			uint32 DensityMapSize = DensityData.Num();
			// Get the global shader map
			TShaderMapRef<FMyComputeShader> MyComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

			// Use RDG for GPU resource management
			FRDGBuilder GraphBuilder(RHICmdList);
			// Create GPU Buffer

			FRDGBufferRef VerticesOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(FVector4f), NumVertices);
			uint32 Divisor = 3;
			FRDGBufferRef TrianglesOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(FIntVector), FMath::DivideAndRoundUp(NumVertices, Divisor));
			FRDGBufferRef DensityBuffer = CreateAndFillBuffer(
				GraphBuilder,
				DensityData.GetData(),
				sizeof(float),
				DensityMapSize,
				TEXT("Density Data Buffer")
			);

			// Create an UAV Buffer to enable RW on GPU Buffer

			FRDGBufferUAVRef VerticesOutputBufferUAV = GraphBuilder.CreateUAV(VerticesOutputBuffer, PF_R32_UINT);
			FRDGBufferUAVRef TrianglesOutputBufferUAV = GraphBuilder.CreateUAV(TrianglesOutputBuffer);
			FRDGBufferUAVRef DensityBufferUAV = GraphBuilder.CreateUAV(DensityBuffer, PF_R32_FLOAT);

			AddClearUAVPass(GraphBuilder, VerticesOutputBufferUAV, 0);
			// Allocate parameters
			FMyComputeShader::FParameters* PassParameters = GraphBuilder.AllocParameters<FMyComputeShader::FParameters>();

			PassParameters->Vertices = VerticesOutputBufferUAV;
			PassParameters->Triangles = TrianglesOutputBufferUAV;
			PassParameters->DensityMap = DensityBufferUAV;

			// Dispatch the compute shader using FComputeShaderUtils
			// Number of Thread Groups
			const uint32 ThreadGroupSize = 8;
			FIntVector NumOfThreadGroups(
				FMath::DivideAndRoundUp(NumVertices, ThreadGroupSize),
				FMath::DivideAndRoundUp(NumVertices, ThreadGroupSize),
				FMath::DivideAndRoundUp(NumVertices, ThreadGroupSize));
			
			FIntVector ConstNumOfThreadGroups(
				1,
				1,
				1);

			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("ComputeShaderPass"),
				MyComputeShader,
				PassParameters,
				ConstNumOfThreadGroups
			);

			FRHIGPUBufferReadback* VerticesReadbackBuffer = new FRHIGPUBufferReadback(TEXT("Vertices Compute Readback"));
			AddEnqueueCopyPass(GraphBuilder, VerticesReadbackBuffer, VerticesOutputBuffer, sizeof(FVector4f) * NumVertices); // Copy (n) bytes (uint32)

			// Execute the RDG Graph
			GraphBuilder.Execute();

			FComputeShaderReadback::ProcessVertexData(World, VerticesReadbackBuffer, sizeof(FVector4f), NumVertices);
		});
}

// Create the buffer to hold data 
FRDGBufferRef FMyComputeShaderWrapper::CreateEmptyBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements)
{
	return GraphBuilder.CreateBuffer(
		FRDGBufferDesc::CreateStructuredDesc(SizeOfElement, NumOfElements),
		TEXT("OutputBuffer")
	);
}

FRDGBufferRef FMyComputeShaderWrapper::CreateAndFillBuffer(FRDGBuilder& GraphBuilder, const void* Data, const uint32& SizeOfElement, const uint32& NumOfElements, const TCHAR* DebugName)
{
	FRDGBufferDesc Desc = FRDGBufferDesc::CreateBufferDesc(
		SizeOfElement,
		NumOfElements
	);
	Desc.Usage = EBufferUsageFlags::UnorderedAccess | EBufferUsageFlags::ShaderResource;
	
	FRDGBufferRef Buffer = GraphBuilder.CreateBuffer(
		Desc,
		DebugName
	);

	GraphBuilder.QueueBufferUpload(
		Buffer,
		Data,
		SizeOfElement * NumOfElements,
		ERDGInitialDataFlags::NoCopy
	);

	return Buffer;
}
