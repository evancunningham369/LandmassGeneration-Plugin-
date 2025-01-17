// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LandmassManager.generated.h"

/**
 * 
 */
UCLASS()
class LANDMASSGENERATION_API ULandmassManager : public UObject
{
	GENERATED_BODY()
	
public:
	static ULandmassManager* Get();

	void SpawnChunks(UWorld* World, float SpawnOffset, int32 NumOfChunksX, int32 NumOfChunksY);
	void SpawnTopRow(UWorld* World, float SpawnOffset, int32 NumOfChunksX, int32 NumOfChunksY);
	void SpawnMiddleRow(UWorld* World, float SpawnOffset, int32 NumOfChunksX, int32 NumOfChunksY);
	void SpawnBottomRow(UWorld* World, float SpawnOffset, int32 NumOfChunksX);

	void CreateTopLeftChunk(float (&TerrainMap)[32][32][8]);
	void CreateTopEdgeChunk(float(&TerrainMap)[32][32][8]);
	void CreateTopRightChunk(float(&TerrainMap)[32][32][8]);

	void CreateLeftEdgeChunk(float(&TerrainMap)[32][32][8]);
	void CreateMiddleChunk(float(&TerrainMap)[32][32][8]);
	void CreateRightEdgeChunk(float(&TerrainMap)[32][32][8]);

	void CreateBottomLeftChunk(float(&TerrainMap)[32][32][8]);
	void CreateBottomEdgeChunk(float(&TerrainMap)[32][32][8]);
	void CreateBottomRightChunk(float(&TerrainMap)[32][32][8]);

	const TArray<TArray<int32>>& GetTriangulationTable() const { return TriangleTable; }
	const TArray<TArray<FVector>>& GetEdgeTable() const { return EdgeTable; }
	const TArray<FIntVector>& GetCornerTable() const { return CornerTable; }
private:

	FVector SpawnLocation{ 0, 0, 0 };

	int32 TerrainWidth = 32;
	int32 TerrainHeight = 8;

	ULandmassManager();
	void InitializeSharedData();

	static ULandmassManager* Instance;

	// Verticies in a cube(8)
	TArray<FIntVector> CornerTable;

	// Edges in a cube(12)
	TArray<TArray<FVector>> EdgeTable;

	// All possible configurations of edges in a cube. 
	// Row selected based on index, calculated by converting "selected" vertices that are inside the mesh into binary, then decimal
	// EX: 7, 6, 5, 4, 3, 2, 1, 0, Selected: 7, 5, 1 
	//     1, 0, 1, 0, 0, 0, 1, 0
	//			index = 162
	// Corresponding row at that index:
	//{ 5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },

	TArray<TArray<int32>> TriangleTable;
};
