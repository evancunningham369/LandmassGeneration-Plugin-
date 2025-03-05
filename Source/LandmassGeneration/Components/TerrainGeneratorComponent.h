// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicMeshComponent.h"
#include "LandmassGeneration/LandmassStructs.h"
#include "TerrainGeneratorComponent.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FTerrainChunkInfo
{
    GENERATED_BODY()

    UPROPERTY()
    FUintVector ChunkCoords;

    UPROPERTY()
    class UTerrainChunkComponent* ChunkComponent;
};

UCLASS()
class LANDMASSGENERATION_API UTerrainGeneratorComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:
    UTerrainGeneratorComponent();

    virtual void BeginDestroy() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    /** Generate terrain with the given parameters */
    void GenerateTerrain(const FTerrainGenerationParams& Params);

    /** Called when compute shader completes */
    void OnComputeShaderComplete(uint32 TriangleCount);

    /** The maximum number of triangles to generate */
    UPROPERTY(EditAnywhere, Category = "Terrain Generation")
    int32 MaxTriangleCount = 500000;

    /** The size of each chunk in voxels */
    UPROPERTY(EditAnywhere, Category = "Terrain Generation", meta = (ClampMin = "8", ClampMax = "64"))
    int32 ChunkSize = 16;

    bool bEnableDebugVisualization = false;

private:
    /** Create chunks based on terrain parameters */
    void CreateChunks(const FTerrainGenerationParams& Params);

    /** Calculate which chunk a point belongs to */
    FIntVector GetChunkCoordsForPoint(const FVector& Point) const;

    FTerrainGenerationParams TerrainParams;

    TMap<FUintVector, TArray<FTriangle>> TriangleChunks;


    UPROPERTY()
    TArray<FTerrainChunkInfo> ChunkInfos;

    UPROPERTY()
    class ULandmassManagerSubsystem* ShaderSubsystem;

    int32 CurrentGenerationRequestId = INDEX_NONE;

    /** Scale used to convert from voxel space to world space */
    float WorldScale = 100.0f;
};
