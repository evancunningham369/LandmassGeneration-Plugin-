// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LandmassGeneration/Landmass/LandmassTypes.h"
#include "LandmassComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LANDMASSGENERATION_API ULandmassComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	ULandmassComponent();

	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* ProceduralMesh;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;

	TMap<FIntVector, TArray<FVector>> VertexGrid;

	ELandmassType LandmassType;

	FVector LandmassOffset;
	FIntVector LandmassOffsetScaleDown;

	float TerrainSurface = 0.f;

	UPROPERTY(EditAnywhere)
	int32 Width = 32;

	UPROPERTY(EditAnywhere)
	int32 Height = 8;

	float TerrainMap[32][32][8];

	UPROPERTY(EditAnywhere)
	float GridCellSize = 300.f;


	int32 ConfigIndex = 0;

	UPROPERTY(EditAnywhere)
	bool bUsePerlinNoise = false;
	void InitializeLandmassOffsets(FVector Offset);
	void GetEffectedVectors(const FVector& Point, const FBox& BoundingBox);
	void ReCreateMesh(const FVector& HitLocation, float Radius);
	void PopulateTerrainMap();

	void PopulateVertexGrid();

	FIntVector GetGridCellIndex(const FVector& Vertex);
	int32 GetScalarIndex(FVector LocalPosition);

	void MarchCube(FVector position, TArray<float> Cube);
	void TestMarchCube(FVector position, int32 Index);
	int32 GetCubeConfiguration(TArray<float> Cube);
	void ClearMeshData();

	void CreateMeshData();

	void PrintVertexGrid();
	void DrawVectors(const TArray<FVector>& Vectors);
	void RemoveMesh(const FHitResult& HitResult, float Radius, const FVector& HitDirection);
	void MoveVectorFromExplosion(FVector& Vertex);
	void BuildMesh(bool bUpdateMesh = false);
	void BuildTestCube();
	void BuildTestTriangle();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE void SetLandmassType(ELandmassType LandmassMeshType) { LandmassType = LandmassMeshType; }
};
