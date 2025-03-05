// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include <LandmassGeneration/LandmassStructs.h>
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
		const FTerrainGenerationParams& Params,
		TMap<FUintVector, TArray<FTriangle>>& TriangleChunks,
		TFunction<void(uint32)> Callback);

	void CancelRequest(int32 RequestId);

private:
	TArray<float> DensityData;
	void ProcessShaderReadback(
		FRHIGPUBufferReadback* ReadbackBuffer, 
		TMap<FUintVector, TArray<FTriangle>>& TriangleChunks,
		FUintVector& ChunkCoords,
		int32 ProcessedChunks, 
		const int32& TotalChunks ,
		int32 RequestId, 
		uint32 ElementSize,
		uint32 NumTrianglesPerChunk);

	TMap<int32, TFunction<void(uint32)>> PendingCallbacks;
	//TMap<FIntVector, TArray<FTriangle>> TriangleChunks;

	int32 NextRequestId;

	void AddDensityCubesShaderPass(
		const FTerrainGenerationParams& Params, 
		const int32& TotalChunks ,
		UWorld* World, 
		FRDGBuilder& GraphBuilder, 
		FRDGTextureUAVRef& DensityUAV);

	FRDGBufferRef CreateEmptyBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements);
	FRDGTextureRef CreateTextureBuffer(FRDGBuilder& GraphBuilder, const FTerrainGenerationParams& Params, const void* Data, const uint32& SizeOfElement, const uint32& NumOfElements, const TCHAR* DebugName);
};
