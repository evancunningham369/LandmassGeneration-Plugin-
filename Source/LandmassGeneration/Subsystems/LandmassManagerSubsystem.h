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
		TFunction<void(const TArray<FTriangle>&, uint32)> Callback);

	void CancelRequest(int32 RequestId);

private:
	TArray<float> DensityData;
	void ProcessShaderReadback(FRHIGPUBufferReadback* ReadbackBuffer, int32 RequestId, uint32 ElementSize, uint32 TotalElements);

	TMap<int32, TFunction<void(const TArray<FTriangle>&, uint32)>> PendingCallbacks;

	int32 NextRequestId;

	void AddDensityCubesShaderPass(const FTerrainGenerationParams& Params, UWorld* World, FRDGBuilder& GraphBuilder, FRDGTextureUAVRef& DensityUAV);

	FRDGBufferRef CreateEmptyBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements);
	FRDGTextureRef CreateTextureBuffer(FRDGBuilder& GraphBuilder, const void* Data, const uint32& SizeOfElement, const uint32& NumOfElements, const TCHAR* DebugName);
};
