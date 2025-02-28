// Fill out your copyright notice in the Description page of Project Settings.

#include "LandmassManagerSubsystem.h"
#include "LandmassGeneration/Landmass/Landmass.h"
#include "RenderGraphBuilder.h"         // Required for FRDGBuilder
#include <LandmassGeneration/Shaders/LandmassComputeShader.h>
#include <RenderGraphUtils.h>

int32 ULandmassManagerSubsystem::RequestTerrainGeneration(
	const FTerrainGenerationParams& Params, 
	TFunction<void(const TArray<FTriangle>&, uint32)> Callback)
{
	int32 RequestId = NextRequestId++;
	PendingCallbacks.Add(RequestId, Callback);

	ENQUEUE_RENDER_COMMAND(TerrainGenerationCommand)(
		[this, Params, RequestId](FRHICommandListImmediate& RHICmdList)
		{
			FRDGBuilder GraphBuilder(RHICmdList);

			// Density pass
			FRDGTextureUAVRef DensityUAV;
			AddDensityCubesShaderPass(Params, GetWorld(), GraphBuilder, DensityUAV);

			// Marching cubes pass
			uint32 NumTriangles = (Params.Width * Params.Depth) / 2; // You should calculate this based on your needs
			FRDGBufferRef TrianglesOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(FTriangle), NumTriangles);
			FRDGBufferRef CounterOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(uint32), 1);

			FRDGBufferUAVRef TrianglesOutputBufferUAV = GraphBuilder.CreateUAV(TrianglesOutputBuffer);
			FRDGBufferUAVRef CounterOutputBufferUAV = GraphBuilder.CreateUAV(CounterOutputBuffer, PF_R32_UINT);

			AddClearUAVPass(GraphBuilder, CounterOutputBufferUAV, 0);

			TShaderMapRef<FMarchingCubesShader> MarchingCubesShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
			FMarchingCubesShader::FParameters* MarchingCubesParams = GraphBuilder.AllocParameters<FMarchingCubesShader::FParameters>();
			MarchingCubesParams->Triangles = TrianglesOutputBufferUAV;
			MarchingCubesParams->DensityMap = DensityUAV;
			MarchingCubesParams->Counter = CounterOutputBufferUAV;
			MarchingCubesParams->VolumeSize = FUintVector3(Params.Width, Params.Height, Params.Depth);


			const uint32 ThreadGroupSize = 8;

			FIntVector MarchingCubesThreadGroups(
				FMath::DivideAndRoundUp(Params.Width, ThreadGroupSize),
				FMath::DivideAndRoundUp(Params.Width, ThreadGroupSize),
				1);


			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("Marching Cubes Shader Pass"),
				MarchingCubesShader,
				MarchingCubesParams,
				MarchingCubesThreadGroups
			);

			// Setup readback
			FRHIGPUBufferReadback* TriangleReadbackBuffer = new FRHIGPUBufferReadback(TEXT("Triangle Compute Readback"));
			AddEnqueueCopyPass(GraphBuilder, TriangleReadbackBuffer, TrianglesOutputBuffer, sizeof(FTriangle) * NumTriangles);

			// Add completion handler
				GraphBuilder.AddPass(
					RDG_EVENT_NAME("ProcessTerrainData"),
					ERDGPassFlags::None,
					[this, NumTriangles ,TriangleReadbackBuffer, RequestId](FRHICommandListImmediate& RHICmdList)
					{
						// Process the readback with the correct parameters
						ProcessShaderReadback(TriangleReadbackBuffer, RequestId, sizeof(FTriangle), NumTriangles);
					});

			// Execute graph ONCE, at the end
			GraphBuilder.Execute();
		});

	return RequestId;
}

void ULandmassManagerSubsystem::ProcessShaderReadback(FRHIGPUBufferReadback* ReadbackBuffer, int32 RequestId, uint32 ElementSize, uint32 TotalElements)
{
	TFunction<void(const TArray<FTriangle>&, uint32)>* Callback = PendingCallbacks.Find(RequestId);
	if (!Callback)
	{
		delete ReadbackBuffer;
		return;
	}

	TArray<FTriangle> Triangles;
	uint32 TriangleCount = 0;

	if (ReadbackBuffer)
	{
		void* Data = ReadbackBuffer->Lock(TotalElements * ElementSize);
		if (Data)
		{
			FTriangle* TriangleData = static_cast<FTriangle*>(Data);

			TriangleCount = TotalElements;

			Triangles.SetNum(TotalElements);
			FMemory::Memcpy(Triangles.GetData(), TriangleData, TriangleCount * ElementSize);

			ReadbackBuffer->Unlock();
		}
		delete ReadbackBuffer;
	}
	AsyncTask(ENamedThreads::GameThread, [Triangles, TriangleCount, Callback, this, RequestId]()
		{
			(*Callback)(Triangles, TriangleCount);

			PendingCallbacks.Remove(RequestId);
		});
}

void ULandmassManagerSubsystem::AddDensityCubesShaderPass(
	const FTerrainGenerationParams& Params, UWorld* World, 
	FRDGBuilder& GraphBuilder, 
	FRDGTextureUAVRef& DensityUAV)
{
	TShaderMapRef<FDensityComputeShader> DensityShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	// Use RDG for GPU resource management
	// Create GPU Buffer

	FRDGTextureRef DensityBuffer = CreateTextureBuffer(
		GraphBuilder,
		DensityData.GetData(),
		sizeof(float),
		Params.NumVertices,
		TEXT("Density Data Buffer")
	);

	// Create an UAV Buffer to enable RW on GPU Buffer
	DensityUAV = GraphBuilder.CreateUAV(FRDGTextureUAVDesc(DensityBuffer));

	// Allocate parameters
	FDensityComputeShader::FParameters* DensityParams = GraphBuilder.AllocParameters<FDensityComputeShader::FParameters>();
	DensityParams->DensityMap = DensityUAV;


	// Dispatch the compute shader using FComputeShaderUtils
	// Number of Thread Groups
	const uint32 ThreadGroupSize = 8;

	FIntVector DensityThreadGroups(
		FMath::DivideAndRoundUp(Params.Width , ThreadGroupSize),
		FMath::DivideAndRoundUp(Params.Width , ThreadGroupSize),
		1);

	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("Density Shader Pass"),
		DensityShader,
		DensityParams,
		DensityThreadGroups
	);
}

FRDGBufferRef ULandmassManagerSubsystem::CreateEmptyBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements)
{
	return GraphBuilder.CreateBuffer(
		FRDGBufferDesc::CreateStructuredDesc(SizeOfElement, NumOfElements),
		TEXT("OutputBuffer")
	);
}

FRDGTextureRef ULandmassManagerSubsystem::CreateTextureBuffer(FRDGBuilder& GraphBuilder, const void* Data, const uint32& SizeOfElement, const uint32& NumOfElements, const TCHAR* DebugName)
{
	FRDGTextureDesc Desc = FRDGTextureDesc::Create3D(
		FIntVector(2, 2, 2),
		PF_R32_FLOAT,
		FClearValueBinding::None,
		TexCreate_UAV | TexCreate_ShaderResource
	);

	FRDGTexture* Texture = GraphBuilder.CreateTexture(
		Desc,
		DebugName
	);



	return Texture;
}

void ULandmassManagerSubsystem::CancelRequest(int32 RequestId)
{
}