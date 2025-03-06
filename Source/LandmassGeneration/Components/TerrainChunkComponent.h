// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicMeshComponent.h"
#include "LandmassGeneration/LandmassStructs.h"
#include "TerrainChunkComponent.generated.h"

/**
 * 
 */
UCLASS()
class LANDMASSGENERATION_API UTerrainChunkComponent : public UDynamicMeshComponent
{
	GENERATED_BODY()

public:
    UTerrainChunkComponent();

    /** Updates this chunk with the given triangles */
    void UpdateMesh(const TArray<FTriangle>& Triangles, uint32 TriangleCount);

    /** Get chunk coordinates */
    FIntVector GetChunkCoords() const { return ChunkCoords; }

    /** Set chunk coordinates */
    void SetChunkCoords(const FIntVector& InCoords) { ChunkCoords = InCoords; }

	TSharedPtr<FTerrainChunkData> GetChunkData() const { return ChunkData; }

	void SetChunkData(TSharedPtr<FTerrainChunkData> InChunkData) { ChunkData = InChunkData; }

    void UpdateMeshFromSharedData();

private:
	TSharedPtr<FTerrainChunkData> ChunkData;

    FDynamicMesh3 Mesh;
    FIntVector ChunkCoords;
};
