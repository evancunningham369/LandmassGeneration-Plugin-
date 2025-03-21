// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include <LandmassGeneration/LandmassStructs.h>
#include <LandmassGeneration/Components/TerrainGeneratorComponent.h>
#include "LandmassManagerSubsystem.generated.h"

/**
 * 
 */

UCLASS()
class LANDMASSGENERATION_API ULandmassManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	int32 RequestTerrainGeneration(
		const TArray<FTerrainChunkInfo>& ChunkInfos,
		uint32 ChunkSize,
		uint32 TotalChunks,
		TFunction<void()> Callback);

	void TestShader(const TArray<FTerrainChunkInfo>& ChunkInfos, uint32 ChunkSize);

	void CancelRequest(int32 RequestId);

private:
	TArray<float> DensityData;
	TMap<TSharedPtr<FRHIGPUBufferReadback>, TSharedPtr<FTerrainChunkData>> TriangleReadbackBuffers;
	TArray<TSharedPtr<FRHIGPUBufferReadback>> ReadbackBuffers;
	int32 TestNumElementsPerChunk;
	void ProcessShaderReadback(
		TSharedPtr<FRHIGPUBufferReadback> ReadbackBuffer,
		TSharedPtr<FTerrainChunkData> ChunkData,
		TSharedPtr<int32> ProcessedChunks, 
		const int32& TotalChunks ,
		int32 RequestId, 
		uint32 ElementSize,
		uint32 NumTrianglesPerChunk);

	TMap<int32, TFunction<void()>> PendingCallbacks;
	//TMap<FIntVector, TArray<FTriangle>> TriangleChunks;

	int32 NextRequestId;

	void AddDensityCubesShaderPass(
		const uint32& ChunkSize,
		const FIntVector& ChunkCoords,
		UWorld* World, 
		FRDGBuilder& GraphBuilder, 
		FRDGTextureUAVRef& DensityUAV);

	void AddEditDensityCubesShaderPass(
		const uint32& ChunkSize,
		const FIntVector& ChunkCoords,
		UWorld* World,
		FRDGBuilder& GraphBuilder,
		FRDGTextureUAVRef& DensityUAV);

	FRDGBufferRef CreateEmptyBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements);
	FRDGTextureRef CreateTextureBuffer(FRDGBuilder& GraphBuilder, const uint32& ChunkSize, const TCHAR* DebugName);
};
