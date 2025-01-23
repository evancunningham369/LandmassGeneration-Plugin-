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
	int32 Width = 4;

	UPROPERTY(EditAnywhere)
	int32 Height = 8;

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
	void ReCreateMesh(const FVector& WorldHitLocation, const FVector& LocalHitLocation, float Radius);
	void PopulateTerrainMap();

	FIntVector GetGridCellIndex(const FVector& Vertex);
	int32 GetScalarIndex(FVector LocalPosition);

	void MarchCube(FVector position, TArray<float> Cube);
	int32 GetCubeConfiguration(TArray<float> Cube);
	void ClearMeshData();

	void CreateMeshData();

	void PrintVertexGrid();
	void DrawVectors(const TArray<FVector>& Vectors);
	void RemoveMesh(const FHitResult& HitResult, float Radius, const FVector& HitDirection);
	void BuildMesh();
	void BuildTestCube();
	void BuildTestTriangle();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE void SetLandmassType(ELandmassType LandmassMeshType) { LandmassType = LandmassMeshType; }
};
