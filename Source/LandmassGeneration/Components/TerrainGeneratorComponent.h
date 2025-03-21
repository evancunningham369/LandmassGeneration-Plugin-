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
    FIntVector ChunkCoords;

    UPROPERTY()
    class UTerrainChunkComponent* ChunkComponent;

	TSharedPtr<FTerrainChunkData> ChunkData;
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
    void OnComputeShaderComplete();

	bool bIsEdit = false;

    /** The maximum number of triangles to generate */
    UPROPERTY(EditAnywhere, Category = "Terrain Generation")
    int32 MaxTriangleCount = 500000;

    int32 ChunksX = 1;
    int32 ChunksY = 1;
    int32 ChunksZ = 1;

    // Chunk size
    UPROPERTY(VisibleAnywhere, Category = "Terrain Generation")
    int32 ChunkSize = 8;

    bool bEnableDebugVisualization = false;

private:
    /** Create chunks based on terrain parameters */
    void CreateChunks(const FTerrainGenerationParams& Params);

    /** Calculate which chunk a point belongs to */
    FIntVector GetChunkCoordsForPoint(const FVector& Point) const;

    FTerrainGenerationParams TerrainParams;

	// Map of chunk coordinates to triangle data
    TMap<FIntVector, TSharedPtr<FTerrainChunkData>> ChunkDataMap;


    UPROPERTY()
    TArray<FTerrainChunkInfo> ChunkInfos;

    UPROPERTY()
    class ULandmassManagerSubsystem* ShaderSubsystem;

    int32 CurrentGenerationRequestId = INDEX_NONE;

    /** Scale used to convert from voxel space to world space */
    float WorldScale = 100.0f;
};
