// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <LandmassGeneration/LandmassStructs.h>
#include "Components/HierarchicalInstancedStaticMeshComponent.h" // Include HISM header
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
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USimpleTriangleComponent* SimpleTriangleComponent;

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
    virtual void Tick(float DeltaTime) override;
    virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(VisibleAnywhere)
    UHierarchicalInstancedStaticMeshComponent* HISMComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (ToolTip = "Half-dimensions (X,Y,Z) of the spawning volume centered on the actor"))
    FVector SpawnBoxExtents = FVector(50000.0f, 50000.0f, 0.0f); // Default to a 40m x 40m x 2m box

    UPROPERTY(EditAnywhere, Category = "Grass Spawning")
    int32 NumInstances = 3000000;

    UPROPERTY(EditAnywhere, Category = "Grass Spawning")
    float SpawnRadius = 2000.0f;

private:
    void GenerateGrassInstances();
    void GenerateGrass();
};
