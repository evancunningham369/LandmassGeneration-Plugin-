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

	UMaterialInstance* GrassMaterial;

	UMaterialInstance* SoilMaterial;

	TArray<float> TerrainMap;

	int32 GetTerrainMapIndex(int32 X, int32 Y, int32 Z) const;
	void GetTerrainMapCoordinates(int32 Index, int32& OutX, int32& OutY, int32& OutZ) const;
	void SetTerrainMapValue(int32 X, int32 Y, int32 Z, float Value);
	float GetTerrainMapValue(int32 X, int32 Y, int32 Z) const;
	void DebugPrintTerrainMap();

	UPROPERTY(EditAnywhere)
	float GridCellSize = 300.f;

	FBox SphereBoundingBox;

	int32 ConfigIndex = 0;

	UPROPERTY(EditAnywhere)
	bool bUsePerlinNoise = false;
	void InitializeLandmassOffsets(FVector Offset);
	void PopulateTerrainMap();
	void CreateMeshData();
	void MarchCube(FVector position, TArray<float> Cube);
	int32 GetCubeConfiguration(TArray<float> Cube);
	void BuildMesh();

	void UpdateBodyCollision();
	
	void CreateMesh(int32 TerrainWidth, int32 TerrainHeight);
	void ReCreateMesh(const FVector& WorldHitLocation, float Radius);
	void ResetMesh();
	void ClearMeshData();

	void AssignTriangleMaterials();

	FIntVector GetGridCellIndex(const FVector& Vertex);
	int32 GetScalarIndex(FVector LocalPosition);

	// Test Functions
	void PrintVertexGrid();
	void DrawVectors();
	void BuildTestCube();
	void BuildTestTriangle();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE void SetLandmassType(ELandmassType LandmassMeshType) { LandmassType = LandmassMeshType; }
	FORCEINLINE void SetTerrainMaterials(UMaterialInstance* TerrainSoilMaterial, UMaterialInstance* TerrainGrassMaterial) { SoilMaterial = TerrainSoilMaterial; GrassMaterial = TerrainGrassMaterial; }
};
