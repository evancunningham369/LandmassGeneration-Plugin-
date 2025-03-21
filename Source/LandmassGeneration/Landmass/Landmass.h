// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <LandmassGeneration/LandmassStructs.h>
#include "Landmass.generated.h"


UENUM(BlueprintType)
enum class ETerrainQuality : uint8
{
    Low UMETA(DisplayName = "Low"),
    Medium UMETA(DisplayName = "Medium"),
    High UMETA(DisplayName = "High"),
    Ultra UMETA(DisplayName = "Ultra"),
    Custom UMETA(DisplayName = "Custom")
};

UCLASS()
class LANDMASSGENERATION_API ALandmass : public AActor
{
	GENERATED_BODY()
	
public:
    ALandmass();

    class UTerrainGeneratorComponent* TerrainGeneratorComponent;

    // Quality presets
    UPROPERTY(EditAnywhere, Category = "Terrain Generation")
    ETerrainQuality TerrainQuality = ETerrainQuality::Low;

    // Custom terrain settings (only used when TerrainQuality = Custom)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Generation", meta = (EditCondition = "TerrainQuality == ETerrainQuality::Custom", ClampMin = "8", ClampMax = "512"))
    int32 CustomTerrainWidth = 16;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Generation", meta = (EditCondition = "TerrainQuality == ETerrainQuality::Custom", ClampMin = "8", ClampMax = "512"))
    int32 CustomTerrainHeight = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Generation", meta = (EditCondition = "TerrainQuality == ETerrainQuality::Custom", ClampMin = "8", ClampMax = "512"))
    int32 CustomTerrainDepth = 16;

    // Maximum number of triangles to generate
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Generation", meta = (ClampMin = "10000", ClampMax = "5000000"))
    int32 MaxTriangles = 500000;

    // Debug visualization
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    bool bEnableDebugVisualization = false;

    UPROPERTY(EditAnywhere, Category = "Terrain Generation")
    bool bIsEdit = false;

    // Regenerate terrain
    UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
    void RegenerateTerrain();

protected:
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

private:
    FTerrainGenerationParams BuildTerrainParams() const;

};
