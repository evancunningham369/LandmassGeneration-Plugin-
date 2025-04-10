// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <LandmassGeneration/LandmassStructs.h>
#include "Landmass.generated.h"

UCLASS()
class LANDMASSGENERATION_API ALandmass : public AActor
{
	GENERATED_BODY()
	
public:
    ALandmass();
    class UTerrainGeneratorComponent* TerrainGeneratorComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UGrassGeneratorComponent* GrassGeneratorComponent;

    // Maximum number of triangles to generate
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Generation", meta = (ClampMin = "10000", ClampMax = "5000000"))
    int32 MaxTriangles = 500000;

    // Debug visualization
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    bool bEnableDebugVisualization = false;

    UPROPERTY(EditAnywhere, Category = "Terrain Generation")
    bool bIsEdit = false;

    UPROPERTY(EditAnywhere, Category = "Grass")
    bool bEnableGrass = true;

    // Regenerate terrain
    UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
    void RegenerateTerrain();

    UFUNCTION(BlueprintCallable, Category = "Grass")
    void RegenerateGrass();

protected:
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

};
