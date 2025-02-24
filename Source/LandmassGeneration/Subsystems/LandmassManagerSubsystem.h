// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LandmassManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LANDMASSGENERATION_API ULandmassManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	void SpawnChunks();
	void SpawnChunk();
	void CreateMap();

	void PopulateDensityData();

	void SetTerrainMapValue(int32 X, int32 Y, int32 Z, float Value);

private:
	// Density Map
	TArray<float> DensityData;

	// Number of vertices wide
	int32 Width = 2;

	// Number of vertices high
	int32 Height = 2;

	// Number of chunks in the X direction
	UPROPERTY(EditAnywhere)
	int32 NumOfChunksX = 2;

	// Number of chunks in the Y direction
	UPROPERTY(EditAnywhere)
	int32 NumOfChunksY = 2;

	// Number of chunks in the Z direction
	int32 NumOfChunksZ = 1;

	UPROPERTY()
	TArray<TWeakObjectPtr<class ALandmass>> SpawnedLandmasses;
};
