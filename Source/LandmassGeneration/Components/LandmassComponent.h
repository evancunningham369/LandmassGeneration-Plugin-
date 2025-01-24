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

	class UDynamicMeshComponent* DynamicMesh;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;

	TMap<FIntVector, TArray<FVector>> VertexGrid;

	ELandmassType LandmassType;

	FVector LandmassOffset;
	FIntVector LandmassOffsetScaleDown;

	UPROPERTY(EditAnywhere)
	float GridCellSize = 300.f;

	FBox SphereBoundingBox;

	int32 ConfigIndex = 0;

	UPROPERTY(EditAnywhere)
	bool bUsePerlinNoise = false;
	void InitializeLandmassOffsets(FVector Offset);
	void ReCreateMesh(const FVector& WorldHitLocation, const FVector& LocalHitLocation, float Radius);

	FIntVector GetGridCellIndex(const FVector& Vertex);

	void PrintVertexGrid();
	void DrawVectors(const TArray<FVector>& Vectors);
	void RemoveMesh(const FHitResult& HitResult, float Radius, const FVector& HitDirection);
	void BuildTestCube();
	void BuildTestTriangle();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE void SetLandmassType(ELandmassType LandmassMeshType) { LandmassType = LandmassMeshType; }
};
