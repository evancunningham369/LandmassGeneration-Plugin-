// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicMeshComponent.h"
#include "LandmassGeneration/LandmassStructs.h"
#include "TerrainGeneratorComponent.generated.h"

/**
 * 
 */
UCLASS()
class LANDMASSGENERATION_API UTerrainGeneratorComponent : public UDynamicMeshComponent
{
	GENERATED_BODY()
	
public:
	UTerrainGeneratorComponent();

	void GenerateTerrain(const FTerrainGenerationParams& Params);

	void OnComputeShaderComplete(const TArray<FTriangle>& Triangles, uint32 TriangleCount);
	void DrawTriangle();

private:
	FDynamicMesh3 Mesh;

	FTerrainGenerationParams TerrainParams;

	UPROPERTY()
	class ULandmassManagerSubsystem* ShaderSubsystem;

	int32 CurrentGenerationRequestId;
};
