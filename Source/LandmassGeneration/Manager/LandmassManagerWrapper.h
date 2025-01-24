// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DynamicMeshComponent.h"
#include "LandmassManagerWrapper.generated.h"

UCLASS()
class LANDMASSGENERATION_API ALandmassManagerWrapper : public AActor
{
	GENERATED_BODY()
	
public:	
	ALandmassManagerWrapper();

	UPROPERTY(VisibleAnywhere)
	class UDynamicMeshComponent* DynamicMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;

	float TerrainSurface = 0.f;

	int32 Width = 32;
	int32 Height = 8;

	TArray<float> TerrainMap;

	FDynamicMesh3 Mesh;

	// Dynamic Mesh functions
	void UpdateMesh(const FHitResult& HitResult);
	void ReCreateMesh(const FVector& WorldHitLocation);
	void ResetMesh();
	// Marching cubes functions
	void PopulateTerrainMap();
	void CreateMeshData();
	void MarchCube(FVector position, TArray<float> Cube);
	int32 GetCubeConfiguration(TArray<float> Cube);
	int32 GetScalarIndex(FVector LocalPosition);

	// Terrain Map helper functions
	int32 GetTerrainMapIndex(int32 X, int32 Y, int32 Z) const;
	void GetTerrainMapCoordinates(int32 Index, int32& OutX, int32& OutY, int32& OutZ) const;
	void SetTerrainMapValue(int32 X, int32 Y, int32 Z, float Value);
	float GetTerrainMapValue(int32 X, int32 Y, int32 Z) const;
	void DebugPrintTerrainMap();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

};
