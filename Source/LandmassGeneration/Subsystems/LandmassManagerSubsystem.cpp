// Fill out your copyright notice in the Description page of Project Settings.

#include "LandmassManagerSubsystem.h"
#include "LandmassGeneration/Landmass/Landmass.h"
#include "RenderGraphBuilder.h"         // Required for FRDGBuilder
#include <LandmassGeneration/Shaders/LandmassComputeShader.h>
#include <RenderGraphUtils.h>
#include <LandmassGeneration/DebugMacros.h>

int32 ULandmassManagerSubsystem::RequestTerrainGeneration(
	const FTerrainGenerationParams& Params, 
	const FIntVector& ChunkCount,
	const uint32& ChunkSize,
	TMap<FIntVector, TSharedPtr<FTerrainChunkData>>& ChunkDataMap,
	TFunction<void()> Callback)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Requesting Terrain Generation..."));

	int32 RequestId = NextRequestId++;
	PendingCallbacks.Add(RequestId, Callback);
	
	int32 ChunksX = ChunkCount.X;
	int32 ChunksY = ChunkCount.Y;
	int32 ChunksZ = ChunkCount.Z;


	TSharedPtr<int32> ProcessedChunks = MakeShared<int32>(0);

	const int32 TotalChunks = ChunksX * ChunksY * ChunksZ;

	UE_LOG(LogTemp, Warning, TEXT("Total Chunks: %d"), TotalChunks);
	
	UE_LOG(LogTemp, Warning, TEXT("Chunk Size: %d\n ChunksX: %d\n ChunksY: %d\n ChunksZ: %d"), ChunkSize, ChunksX, ChunksY, ChunksZ);
	ENQUEUE_RENDER_COMMAND(TerrainGenerationCommand)(
		[this, Params, RequestId, &ChunkDataMap ,&ChunkSize, ChunksX, ChunksY, ChunksZ, ProcessedChunks, TotalChunks](FRHICommandListImmediate& RHICmdList)
		{
			FRDGBuilder GraphBuilder(RHICmdList);

			// Density pass
			FRDGTextureUAVRef DensityUAV;
			AddDensityCubesShaderPass(Params, TotalChunks ,GetWorld(), GraphBuilder, DensityUAV);
			
			TMap<FIntVector, FRHIGPUBufferReadback*> TriangleReadbackBuffers;
			uint32 NumTrianglesPerChunk = 0;
			for (int32 X = 0; X < ChunksX; X++)
			{
				for (int32 Y = 0; Y < ChunksY; Y++)
				{
					for (int32 Z = 0; Z < ChunksZ; Z++)
					{

						// Marching cubes pass
						NumTrianglesPerChunk = (Params.Width - 1) * (Params.Depth - 1) * 2; // You should calculate this based on your needs
						FRDGBufferRef TrianglesOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(FTriangle), NumTrianglesPerChunk);
						FRDGBufferRef CounterOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(uint32), 1);

						FRDGBufferUAVRef TrianglesOutputBufferUAV = GraphBuilder.CreateUAV(TrianglesOutputBuffer);
						FRDGBufferUAVRef CounterOutputBufferUAV = GraphBuilder.CreateUAV(CounterOutputBuffer, PF_R32_UINT);

						AddClearUAVPass(GraphBuilder, CounterOutputBufferUAV, 0);

						TShaderMapRef<FMarchingCubesShader> MarchingCubesShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
						FMarchingCubesShader::FParameters* MarchingCubesParams = GraphBuilder.AllocParameters<FMarchingCubesShader::FParameters>();
						MarchingCubesParams->Triangles = TrianglesOutputBufferUAV;
						MarchingCubesParams->DensityMap = DensityUAV;
						MarchingCubesParams->Counter = CounterOutputBufferUAV;
						MarchingCubesParams->VolumeSize = FIntVector(Params.Width, Params.Depth, Params.Height);
						MarchingCubesParams->ChunkCoords = FIntVector(X, Y, Z); // Pass chunk coordinates
						MarchingCubesParams->ChunkSize = ChunkSize; // Pass chunk size


						const uint32 ThreadGroupSize = 8;

						FIntVector MarchingCubesThreadGroups(
							FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize),
							FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize),
							FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize));


						FComputeShaderUtils::AddPass(
							GraphBuilder,
							RDG_EVENT_NAME("Marching Cubes Shader Pass"),
							MarchingCubesShader,
							MarchingCubesParams,
							MarchingCubesThreadGroups
						);

						// Setup readback
						TUniquePtr<FRHIGPUBufferReadback> TriangleReadbackBuffer = MakeUnique<FRHIGPUBufferReadback>(TEXT("Triangle Compute Readback"));
						AddEnqueueCopyPass(GraphBuilder, TriangleReadbackBuffer.Get(), TrianglesOutputBuffer, sizeof(FTriangle) * NumTrianglesPerChunk);

						TriangleReadbackBuffers.Add(FIntVector(X, Y, Z), TriangleReadbackBuffer.Get());
					}
				}
			}
			// Execute graph for each chunk
			
			GraphBuilder.Execute();
			UE_LOG(LogTemp, Warning, TEXT("Executing Graph..."));
			UE_LOG(LogTemp, Warning, TEXT("\nTotal Chunks : %d \n Triangles Per Chunk: %d"), TotalChunks, NumTrianglesPerChunk);
			
			for (const TPair<FIntVector, FRHIGPUBufferReadback*>& Pair : TriangleReadbackBuffers)
			{
				FIntVector ChunkCoords = Pair.Key;
				FRHIGPUBufferReadback* ReadbackBuffer = Pair.Value;

				ProcessShaderReadback(
					ReadbackBuffer,
					ChunkDataMap,
					ChunkCoords,
					ProcessedChunks, 
					TotalChunks, 
					RequestId, 
					sizeof(FTriangle), 
					NumTrianglesPerChunk);
			}
			
		});
		
	return RequestId;
}

void ULandmassManagerSubsystem::ProcessShaderReadback(
	FRHIGPUBufferReadback* ReadbackBuffer, 
	TMap<FIntVector, TSharedPtr<FTerrainChunkData>>& ChunkDataMap,
	FIntVector& ChunkCoords,
	TSharedPtr<int32> ProcessedChunks, 
	const int32& TotalChunks, 
	int32 RequestId, 
	uint32 ElementSize, 
	uint32 NumTrianglesPerChunk)
{
	FString Value = "ProcessingShaderReadback...";
	PRINT_STRING_ASYNC(Value);

	TSharedPtr<FTerrainChunkData>* ChunkDataPtr = ChunkDataMap.Find(ChunkCoords);
	if (!ChunkDataPtr || !(*ChunkDataPtr).IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("No chunk data found for %s"), *ChunkCoords.ToString());
		return;
	}

	TSharedPtr<FTerrainChunkData> ChunkData = *ChunkDataPtr;

	if (ReadbackBuffer)
	{
		void* Data = ReadbackBuffer->Lock(NumTrianglesPerChunk * ElementSize);
		if (Data)
		{
			FTriangle* TriangleData = static_cast<FTriangle*>(Data);

			ChunkData->Triangles.Reserve(NumTrianglesPerChunk);

			for (uint32 i = 0; i < NumTrianglesPerChunk; i++)
			{
				ChunkData->Triangles.Add(TriangleData[i]);
			}

			ChunkData->TriangleCount = NumTrianglesPerChunk;
			ChunkData->bIsProcessed = true;


			ReadbackBuffer->Unlock();
		}
		else
		{
			Value = "Invalid Data";
			PRINT_STRING_ASYNC(Value);
		}
	}
	else
	{
		Value = "Readback buffer invalid";
		PRINT_STRING_ASYNC(Value);
	}
	int32 CurrentProcessed = FPlatformAtomics::InterlockedIncrement(ProcessedChunks.Get());
	UE_LOG(LogTemp, Warning, TEXT("Processed Chunks: %d of %d"), CurrentProcessed, TotalChunks);

	if (CurrentProcessed == TotalChunks)
	{
		AsyncTask(ENamedThreads::GameThread, [this, TotalChunks ,RequestId]()
			{
				UE_LOG(LogTemp, Warning, TEXT("Processed all %d Chunks"), TotalChunks)
				TFunction<void()>* Callback = PendingCallbacks.Find(RequestId);
				if (Callback)
				{
					(*Callback)();
					PendingCallbacks.Remove(RequestId);
				}
				PendingCallbacks.Remove(RequestId);
			});
	}
}

void ULandmassManagerSubsystem::AddDensityCubesShaderPass(
	const FTerrainGenerationParams& Params,
	const int32& TotalChunks,
	UWorld* World, 
	FRDGBuilder& GraphBuilder, 
	FRDGTextureUAVRef& DensityUAV)
{
	TShaderMapRef<FDensityComputeShader> DensityShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	uint32 TotalVertices = TotalChunks * Params.NumVertices;
	// Use RDG for GPU resource management
	// Create GPU Buffer

	FRDGTextureRef DensityBuffer = CreateTextureBuffer(
		GraphBuilder,
		Params,
		DensityData.GetData(),
		sizeof(float),
		TotalVertices,
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
		FMath::DivideAndRoundUp(Params.Width, ThreadGroupSize),
		FMath::DivideAndRoundUp(Params.Width, ThreadGroupSize),
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

FRDGTextureRef ULandmassManagerSubsystem::CreateTextureBuffer(FRDGBuilder& GraphBuilder, const FTerrainGenerationParams& Params, const void* Data, const uint32& SizeOfElement, const uint32& NumOfElements, const TCHAR* DebugName)
{
	FRDGTextureDesc Desc = FRDGTextureDesc::Create3D(
		FIntVector(Params.Width, Params.Depth, Params.Height),
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
	PendingCallbacks.Remove(RequestId);
}