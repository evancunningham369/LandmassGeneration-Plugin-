// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "LandmassGeneration/LandmassStructs.h"
#include "GrassGeneratorComponent.generated.h"

// Structure to define a type of grass
USTRUCT(BlueprintType)
struct FGrassType
{
    GENERATED_BODY()

    // The static mesh to use for this grass type
    UPROPERTY(EditAnywhere, Category = "Grass")
    UStaticMesh* GrassMesh = nullptr;

    // How dense this grass type should be (instances per square meter)
    UPROPERTY(EditAnywhere, Category = "Grass", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float Density = 10.0f;

    // Minimum and maximum scale variation
    UPROPERTY(EditAnywhere, Category = "Grass")
    FVector MinScale = FVector(0.8f, 0.8f, 0.8f);

    UPROPERTY(EditAnywhere, Category = "Grass")
    FVector MaxScale = FVector(1.2f, 1.2f, 1.2f);

    // Maximum slope angle where this grass can grow (in degrees)
    UPROPERTY(EditAnywhere, Category = "Grass", meta = (ClampMin = "0.0", ClampMax = "90.0"))
    float MaxSlope = 45.0f;

    // Allow random rotation on Z axis
    UPROPERTY(EditAnywhere, Category = "Grass")
    bool bRandomRotation = true;

    // Distance to stop rendering this grass type
    UPROPERTY(EditAnywhere, Category = "Grass")
    float CullDistance = 10000.0f;

    // Material to use for the grass
    UPROPERTY(EditAnywhere, Category = "Grass")
    UMaterialInterface* GrassMaterial = nullptr;
};

// Forward declarations
class FGrassRenderProxy;
class FGrassComponent;

/**
 * Component responsible for generating and managing grass using GPU compute
 */
UCLASS(ClassGroup = (LandmassGeneration), meta = (BlueprintSpawnableComponent))
class LANDMASSGENERATION_API UGrassGeneratorComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UGrassGeneratorComponent();

    // USceneComponent interface
    virtual void OnRegister() override;
    virtual void OnUnregister() override;
    virtual void SendRenderDynamicData_Concurrent() override;
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Generate grass using compute shaders
    UFUNCTION(BlueprintCallable, Category = "Grass Generation")
    void GenerateGrass();

    // Different types of grass to generate
    UPROPERTY(EditAnywhere, Category = "Grass Generation")
    TArray<FGrassType> GrassTypes;

    // Cell size for grass grid (in unreal units)
    UPROPERTY(EditAnywhere, Category = "Grass Generation", meta = (ClampMin = "10.0", ClampMax = "1000.0"))
    float CellSize = 100.0f;

    // Maximum number of grass instances (per type)
    UPROPERTY(EditAnywhere, Category = "Grass Generation", meta = (ClampMin = "1000", ClampMax = "10000000"))
    int32 MaxGrassInstances = 1000000;

    // Whether to update grass in real-time when the terrain changes
    UPROPERTY(EditAnywhere, Category = "Grass Generation")
    bool bUpdateWithTerrain = true;

    // Distance from camera where grass begins to fade
    UPROPERTY(EditAnywhere, Category = "Grass Generation", meta = (ClampMin = "100.0"))
    float FadeStartDistance = 8000.0f;

    // Distance from camera where grass is fully culled
    UPROPERTY(EditAnywhere, Category = "Grass Generation", meta = (ClampMin = "100.0"))
    float FadeEndDistance = 10000.0f;

    // Density multiplier for grass (can be adjusted at runtime)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grass Generation", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float DensityMultiplier = 1.0f;

    // Wind strength for grass animation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grass Generation", meta = (ClampMin = "0.0", ClampMax = "10.0"))
    float WindStrength = 1.0f;

    // Seed for random number generation
    UPROPERTY(EditAnywhere, Category = "Grass Generation")
    int32 RandomSeed = 1337;

protected:
    // Get terrain generator component
    class UTerrainGeneratorComponent* GetTerrainGenerator() const;

    // Update shader parameters
    void UpdateShaderParameters();

    // Initialize render resources
    void SetupRenderResources();

    // Release render resources
    void ReleaseRenderResources();

private:
    // Render proxy for grass rendering
    TSharedPtr<FGrassRenderProxy> GrassRenderProxy;

    // Render components for each grass type
    TArray<TSharedPtr<FGrassComponent>> GrassComponents;

    // Cached terrain generator reference
    UPROPERTY()
    class UTerrainGeneratorComponent* TerrainGenerator;

    // Shader uniform buffer
    FBufferRHIRef GrassParametersBuffer;

    // Whether resources have been initialized
    bool bResourcesInitialized = false;

    // Camera position for LOD calculations
    FVector CameraPosition;

    // Flag to indicate grass needs to be regenerated
    bool bNeedsRegeneration = true;

    // Current world to component transform
    FTransform WorldToComponent;
};
