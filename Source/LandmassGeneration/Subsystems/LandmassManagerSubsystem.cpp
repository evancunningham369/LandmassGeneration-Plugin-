// Fill out your copyright notice in the Description page of Project Settings.

#include "LandmassManagerSubsystem.h"
#include "LandmassGeneration/Landmass/Landmass.h"
#include "RenderGraphBuilder.h"         // Required for FRDGBuilder
#include <LandmassGeneration/Shaders/LandmassComputeShader.h>
#include "LandmassGeneration/Components/TerrainChunkComponent.h"
#include <RenderGraphUtils.h>
#include <LandmassGeneration/DebugMacros.h>
#include <LandmassGeneration/MeshOperation/MeshOperation.h>

int32 ULandmassManagerSubsystem::RequestTerrainGeneration(
	const TArray<FTerrainChunkInfo>& ChunkInfos,
	uint32 ChunkSize,
	uint32 TotalChunks,
	TSharedPtr<FMeshOperation> MeshOperation,
	TFunction<void()> Callback)
{
	TriangleReadbackBuffers.Empty();

	UE_LOG(LogTemp, Warning, TEXT("Requesting Terrain Generation..."));

	int32 RequestId = NextRequestId++;
	PendingCallbacks.Add(RequestId, Callback);

	TSharedPtr<int32> ProcessedChunks = MakeShared<int32>(0);

	// Total cubes * number of triangles per cube
	const uint32 NumTrianglesPerChunk = (ChunkSize - 1) * (ChunkSize - 1) * (ChunkSize - 1) * 5; // You should calculate this based on your needs
	
	UE_LOG(LogTemp, Warning, TEXT("Total Chunks: %d\n Triangles Per Chunk: %d"), TotalChunks, NumTrianglesPerChunk);
	ENQUEUE_RENDER_COMMAND(TerrainGenerationCommand)(
		[this, RequestId, ChunkSize, &ChunkInfos ,ProcessedChunks, TotalChunks, NumTrianglesPerChunk, MeshOperation](FRHICommandListImmediate& RHICmdList)
		{
			FRDGBuilder GraphBuilder(RHICmdList);

			
			
			// Execute graph for each chunk
			
			for (FTerrainChunkInfo ChunkInfo : ChunkInfos)
			{
				// Density pass
				FIntVector ChunkCoords = (FIntVector)ChunkInfo.ChunkComponent->GetComponentLocation();
				ChunkInfo.ChunkData->TriangleCount = NumTrianglesPerChunk;
				FRDGBufferRef TrianglesOutputBuffer;

				MeshOperation->Execute(GraphBuilder, TrianglesOutputBuffer ,ChunkCoords, ChunkSize, ChunkInfo.ChunkData);

				// Setup readback
				TSharedPtr<FRHIGPUBufferReadback> TriangleReadbackBuffer = MakeShared<FRHIGPUBufferReadback>(TEXT("Triangle Compute Readback"));
				AddEnqueueCopyPass(GraphBuilder, TriangleReadbackBuffer.Get(), TrianglesOutputBuffer, sizeof(FTriangle) * NumTrianglesPerChunk);

				TriangleReadbackBuffers.Add(TriangleReadbackBuffer, ChunkInfo.ChunkData);
			}
			// Execute graph for each chunk
			
			GraphBuilder.Execute();
			
			// Loop through TriangleReadback Buffers Map
			for (TPair<TSharedPtr<FRHIGPUBufferReadback>, TSharedPtr<FTerrainChunkData>> Pair : TriangleReadbackBuffers)
			{
				TSharedPtr<FRHIGPUBufferReadback> ReadbackBuffer = Pair.Key;
				TSharedPtr<FTerrainChunkData> ChunkData = Pair.Value;

				ProcessShaderReadback(
					ReadbackBuffer, 
					ChunkData,
					ProcessedChunks, 
					TotalChunks, 
					RequestId, 
					sizeof(FTriangle), 
					NumTrianglesPerChunk);
			}

		});
		
	return RequestId;
}

//void ULandmassManagerSubsystem::TestShader(const TArray<FTerrainChunkInfo>& ChunkInfos, uint32 ChunkSize)
//{
//	TestNumElementsPerChunk = ChunkSize * ChunkSize;
//	ENQUEUE_RENDER_COMMAND(TestShaderCommand)(
//		[this, &ChunkInfos, ChunkSize](FRHICommandListImmediate& RHICmdList)
//		{
//
//			FRDGBuilder GraphBuilder(RHICmdList);
//
//			for(FTerrainChunkInfo ChunkInfo : ChunkInfos)
//			{
//			TShaderMapRef<FTestShader> TestShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
//
//			FTestShader::FParameters* TestParams = GraphBuilder.AllocParameters<FTestShader::FParameters>();
//				FRDGBufferRef TestBuffer = GraphBuilder.CreateBuffer(
//					FRDGBufferDesc::CreateStructuredDesc(sizeof(FVector3f), TestNumElementsPerChunk),
//					TEXT("TestBuffer")
//				);
//				FRDGBufferRef CounterOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(uint32), 1);
//
//
//				FRDGBufferUAVRef TestBufferUAV = GraphBuilder.CreateUAV(TestBuffer);
//				FRDGBufferUAVRef CounterOutputBufferUAV = GraphBuilder.CreateUAV(CounterOutputBuffer, PF_R32_UINT);
//
//				AddClearUAVPass(GraphBuilder, CounterOutputBufferUAV, 0);
//
//				TestParams->TestBuffer = TestBufferUAV;
//				TestParams->TestCounter = CounterOutputBufferUAV;
//				TestParams->ChunkLocation = (FIntVector)ChunkInfo.ChunkComponent->GetComponentLocation(); // Pass chunk coordinates
//
//
//				FComputeShaderUtils::AddPass(
//					GraphBuilder,
//					RDG_EVENT_NAME("Test Shader Pass"),
//					TestShader,
//					TestParams,
//					FIntVector(4, 4, 1)
//				);
//
//				TSharedPtr<FRHIGPUBufferReadback> ReadbackBuffer = MakeShared<FRHIGPUBufferReadback>(TEXT("Test Compute Readback"));
//				AddEnqueueCopyPass(GraphBuilder, ReadbackBuffer.Get(), TestBuffer, sizeof(FVector3f) * TestNumElementsPerChunk);
//				ReadbackBuffers.Add(ReadbackBuffer);
//			}
//			GraphBuilder.Execute();
//			//Create ReadbackBuffer
//			for (TSharedPtr<FRHIGPUBufferReadback> ReadbackBuffer : ReadbackBuffers)
//			{
//				if (ReadbackBuffer)
//				{
//					void* Data = ReadbackBuffer->Lock(sizeof(FVector3f) * TestNumElementsPerChunk);
//					if (Data)
//					{
//						FVector3f* VectorData = static_cast<FVector3f*>(Data);
//						/*for (int32 i = 0; i < TestNumElementsPerChunk; i++)
//						{
//							UE_LOG(LogTemp, Warning, TEXT("Vector %d: %s"), i, *VectorData[i].ToString());
//							DRAW_POINT_PERM(FVector(VectorData[i].X * 100, VectorData[i].Y * 100, VectorData[i].Z), FColor::Red);
//						}
//						*/
//						ReadbackBuffer->Unlock();
//					}
//				}
//			}
//		});
//}

void ULandmassManagerSubsystem::ProcessShaderReadback(
	TSharedPtr<FRHIGPUBufferReadback> ReadbackBuffer,
	TSharedPtr<FTerrainChunkData> ChunkData,
	TSharedPtr<int32> ProcessedChunks, 
	const int32& TotalChunks, 
	int32 RequestId, 
	uint32 ElementSize, 
	uint32 NumTrianglesPerChunk)
{
	FString Value = "ProcessingShaderReadback...";
	PRINT_STRING_ASYNC(Value);

	if (ReadbackBuffer)
	{
		void* Data = ReadbackBuffer->Lock(NumTrianglesPerChunk * ElementSize);
		if (Data)
		{
			FTriangle* TriangleData = static_cast<FTriangle*>(Data);

			for (uint32 i = 0; i < NumTrianglesPerChunk; i++)
			{
				//ChunkData->Triangles.Add(TriangleData[i]);
				
				// print out the triangle vertices
				/*UE_LOG(LogTemp, Warning, TEXT("Triangle %d: %s"), i, *TriangleData[i].Vertex1.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Triangle %d: %s"), i, *TriangleData[i].Vertex2.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Triangle %d: %s"), i, *TriangleData[i].Vertex3.ToString());*/
				AsyncTask(ENamedThreads::GameThread, [this, TriangleData, i]()
					{
						DRAW_POINT_PERM((FVector)TriangleData[i].Vertex1 * 100, FColor::Red);
						DRAW_POINT_PERM((FVector)TriangleData[i].Vertex2 * 100, FColor::Red);
						DRAW_POINT_PERM((FVector)TriangleData[i].Vertex3 * 100, FColor::Red);
					});
			}
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

	AsyncTask(ENamedThreads::GameThread, [CurrentProcessed, TotalChunks]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Processed Chunks: %d of %d"), CurrentProcessed, TotalChunks);
		});
	if (CurrentProcessed == TotalChunks)
	{
		/*AsyncTask(ENamedThreads::GameThread, [this, TotalChunks ,RequestId]()
			{
				UE_LOG(LogTemp, Warning, TEXT("Processed all %d Chunks"), TotalChunks)
				TFunction<void()>* Callback = PendingCallbacks.Find(RequestId);
				if (Callback)
				{
					(*Callback)();
				}
				PendingCallbacks.Remove(RequestId);
			});*/
	}
}

void ULandmassManagerSubsystem::CancelRequest(int32 RequestId)
{
	PendingCallbacks.Remove(RequestId);
}