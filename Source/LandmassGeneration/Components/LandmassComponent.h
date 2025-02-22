// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LandmassGeneration/Landmass/LandmassTypes.h"
#include "Components/DynamicMeshComponent.h"
#include "LandmassComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LANDMASSGENERATION_API ULandmassComponent : public UDynamicMeshComponent
{
	GENERATED_BODY()

public:	
	ULandmassComponent();

	// Collision body
	UPROPERTY(EditAnywhere)
	UBodySetup* CachedBodySetup;

	FDynamicMesh3 Mesh;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;

	TMap<FIntVector, TArray<FVector>> VertexGrid;

	ELandmassType LandmassType;

	FVector LandmassOffset;

	float TerrainSurface = 0.f;

	int32 Width;

	int32 Height;

	// The base-width of each Triangle
	UPROPERTY(EditAnywhere)
	float TerrainWidth = 100.f;

	// The number of squares for the Ground Mesh. Each square is two triangles
	UPROPERTY(EditAnywhere)
	int32 NumSquares = 100;

	UMaterialInstance* GrassMaterial;

	UMaterialInstance* SoilMaterial;

	TArray<float> TerrainMap;

	void CreateTriangle(float XOffset = 100.f, float YOffset = 100.f);
	void CreateSquare(float XOffset = 1000.f, float YOffset = 1000.f);
	void CreateCraterAtLocation(FVector HitLocation = FVector::ZeroVector, float CraterDepth = 100.f);
	void CreateGround();
	void BuildMesh();
	void UpdateMesh();
	void UpdateMeshCollision();

	int32 GetTerrainMapIndex(int32 X, int32 Y, int32 Z) const;
	void GetTerrainMapCoordinates(int32 Index, int32& OutX, int32& OutY, int32& OutZ) const;
	void SetTerrainMapValue(int32 X, int32 Y, int32 Z, float Value);
	float GetTerrainMapValue(int32 X, int32 Y, int32 Z) const;
	void DebugPrintTerrainMap();

	UPROPERTY(EditAnywhere)
	float GridCellSize = 300.f;

	FBox SphereBoundingBox;

	int32 ConfigIndex = 0;

	bool bMeshChanged = false;

	UPROPERTY(EditAnywhere)
	bool bUsePerlinNoise = false;
	void InitializeLandmassOffsets(FVector Offset);
	void PopulateTerrainMap();
	void CreateMeshDataOptimized();
	void MarchCubeOptimized(
		const FVector& position, 
		const float Cube[], 
		const TArray<TArray<int32>>& TriangleTable, 
		const TArray<TArray<FVector>>& EdgeTable,
		FDynamicMesh3& CurrentMesh,
		UE::Geometry::FIndex3i& TriangleIndices
	);
	int32 GetCubeConfiguration(TArray<float> Cube);
	int32 GetCubeConfigurationOptimized(const float Cube[]);
	
	void CreateMesh(int32 TerrainMeshWidth, int32 TerrainMeshHeight);
	void ReCreateMesh(const FVector& WorldHitLocation, float Radius);
	void ReCreateMeshLegacy(const FVector& WorldHitLocation, float Radius);
	void ResetMesh();
	void ClearMeshData();

	FIntVector GetGridCellIndex(const FVector& Vertex);
	int32 GetScalarIndex(FVector LocalPosition);

	// Test Functions
	void PrintVertexGrid();
	void DrawVectors();
	void PrintVectors();
	void BuildTestCube();
	void BuildTestTriangle();
	void CreateTestCrater();

protected:
	virtual void BeginPlay() override;
public:	
	FORCEINLINE void SetLandmassType(ELandmassType LandmassMeshType) { LandmassType = LandmassMeshType; }
	FORCEINLINE void SetTerrainMaterials(UMaterialInstance* TerrainSoilMaterial, UMaterialInstance* TerrainGrassMaterial) { SoilMaterial = TerrainSoilMaterial; GrassMaterial = TerrainGrassMaterial; }
};
