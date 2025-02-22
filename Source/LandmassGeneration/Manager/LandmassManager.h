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

	
	const TArray<TArray<int32>>& GetTriangulationTable() const { return TriangleTable; }
	const TArray<TArray<FVector>>& GetEdgeTable() const { return EdgeTable; }
	const TArray<FIntVector>& GetCornerTable() const { return CornerTable; }
	void DeformLandmasses(const TArray<class ULandmassComponent*>&, FVector HitLocation, float ExplosionRadius);

private:
	
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

