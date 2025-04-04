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
			TSharedPtr<FRHIGPUBufferReadback> CounterReadbackBuffer;
			for (FTerrainChunkInfo ChunkInfo : ChunkInfos)
			{
				// Density pass
				FIntVector ChunkCoords = (FIntVector)ChunkInfo.ChunkComponent->GetComponentLocation();
				ChunkInfo.ChunkData->TriangleCount = NumTrianglesPerChunk;
				FRDGBufferRef TrianglesOutputBuffer;
				FRDGBufferRef CounterOutputBuffer;

				MeshOperation->Execute(GraphBuilder, TrianglesOutputBuffer, CounterOutputBuffer, ChunkCoords, ChunkSize, ChunkInfo.ChunkData);

				// Setup readback
				TSharedPtr<FRHIGPUBufferReadback> TriangleReadbackBuffer = MakeShared<FRHIGPUBufferReadback>(TEXT("Triangle Compute Readback"));
				CounterReadbackBuffer = MakeShared<FRHIGPUBufferReadback>(TEXT("Counter Compute Readback"));
				AddEnqueueCopyPass(GraphBuilder, TriangleReadbackBuffer.Get(), TrianglesOutputBuffer, sizeof(FTriangle) * NumTrianglesPerChunk);
				AddEnqueueCopyPass(GraphBuilder, CounterReadbackBuffer.Get(), CounterOutputBuffer, sizeof(int32));
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
					CounterReadbackBuffer,
					ChunkData,
					RequestId,
					NumTrianglesPerChunk,
					ProcessedChunks,
					TotalChunks);
			}

		});
		
	return RequestId;
}

int32 ULandmassManagerSubsystem::RequestTerrainModification(
	UTerrainChunkComponent& ChunkComponent,
	TSharedPtr<class FMeshOperation> MeshOperation,
	TFunction<void()> Callback)
{

	int32 RequestId = NextRequestId++;
	PendingCallbacks.Add(RequestId, Callback);

	const uint32 NumTriangles = (7) * (7) * (7) * 5;
	ENQUEUE_RENDER_COMMAND(TerrainModificationCommand)(
		[this, RequestId, &ChunkComponent, MeshOperation, Callback](FRHICommandListImmediate& RHICmdList)
		{
			FRDGBuilder GraphBuilder(RHICmdList);
			FIntVector ChunkCoords = ChunkComponent.GetChunkCoords();
			FRDGBufferRef TrianglesOutputBuffer;
			FRDGBufferRef CounterOutputBuffer;

			MeshOperation->Execute(GraphBuilder, TrianglesOutputBuffer, CounterOutputBuffer, ChunkCoords, 8, ChunkComponent.GetChunkData());
			// Setup readback
			TSharedPtr<FRHIGPUBufferReadback> TriangleReadbackBuffer = MakeShared<FRHIGPUBufferReadback>(TEXT("Triangle Compute Readback"));
			TSharedPtr<FRHIGPUBufferReadback> CounterReadbackBuffer = MakeShared<FRHIGPUBufferReadback>(TEXT("Counter Compute Readback"));
			AddEnqueueCopyPass(GraphBuilder, TriangleReadbackBuffer.Get(), TrianglesOutputBuffer, sizeof(FTriangle) * NumTriangles);
			AddEnqueueCopyPass(GraphBuilder, CounterReadbackBuffer.Get(), CounterOutputBuffer, sizeof(int32));

			GraphBuilder.Execute();
			// Loop through TriangleReadback Buffers Map
			TSharedPtr<int32> ProcessedChunks = MakeShared<int32>(0);

			ProcessShaderReadback(
				TriangleReadbackBuffer,
				CounterReadbackBuffer,
				ChunkComponent.GetChunkData(),
				RequestId,
				NumTriangles,
				ProcessedChunks);

		});
	return RequestId;
}

void ULandmassManagerSubsystem::ProcessShaderReadback(
	TSharedPtr<FRHIGPUBufferReadback> ReadbackBuffer,
	TSharedPtr<FRHIGPUBufferReadback> CounterReadbackBuffer,
	TSharedPtr<FTerrainChunkData> ChunkData,
	int32 RequestId,
	uint32 NumTrianglesPerChunk,
	TSharedPtr<int32> ProcessedChunks,
	const int32& TotalChunks)
{
	AsyncTask(ENamedThreads::ActualRenderingThread, [this, ReadbackBuffer, CounterReadbackBuffer, ChunkData, RequestId, NumTrianglesPerChunk, ProcessedChunks, TotalChunks]()
	{
		if (!ReadbackBuffer->IsReady() || !CounterReadbackBuffer->IsReady())
		{
		
					ProcessShaderReadback(ReadbackBuffer, CounterReadbackBuffer, ChunkData, RequestId, NumTrianglesPerChunk, ProcessedChunks, TotalChunks);
			
			return;
		}

		void* CounterData = CounterReadbackBuffer->Lock(sizeof(int32));
		int32 NumTriangles = 0;

		if (CounterData)
		{
			int32* CounterArray = static_cast<int32*>(CounterData);
			NumTriangles = CounterArray[0];
			CounterReadbackBuffer->Unlock();
		}
		
		TArray<FTriangle> Triangles;
		void* TriangleData = ReadbackBuffer->Lock(NumTriangles * sizeof(FTriangle));

		if (TriangleData)
		{
			FTriangle* TriangleArray = static_cast<FTriangle*>(TriangleData);
			for (int32 i = 0; i < NumTriangles; i++)
			{
				Triangles.Add(TriangleArray[i]);
			}
			ReadbackBuffer->Unlock();
		}
	
	AsyncTask(ENamedThreads::GameThread, [this, Triangles, ChunkData, RequestId, ProcessedChunks, TotalChunks]()
	{
		FString Value = "ProcessingShaderReadback...";
		PRINT_STRING_ASYNC(Value);

		ChunkData->Triangles = Triangles;
		ChunkData->bIsProcessed = true;

		int32 CurrentProcessed = FPlatformAtomics::InterlockedIncrement(ProcessedChunks.Get());


		UE_LOG(LogTemp, Warning, TEXT("Processed Chunks: %d of %d"), CurrentProcessed, TotalChunks);

		if (CurrentProcessed == TotalChunks)
		{
			UE_LOG(LogTemp, Warning, TEXT("Processed all %d Chunks"), TotalChunks)
			TFunction<void()>* Callback = PendingCallbacks.Find(RequestId);
			if (Callback)
			{
				(*Callback)();
			}
			PendingCallbacks.Remove(RequestId);
		}
			});
		});
}

void ULandmassManagerSubsystem::CancelRequest(int32 RequestId)
{
	PendingCallbacks.Remove(RequestId);
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