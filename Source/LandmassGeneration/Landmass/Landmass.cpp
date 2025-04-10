// Fill out your copyright notice in the Description page of Project Settings.


#include "Landmass.h"
#include "LandmassGeneration/DebugMacros.h"
#include <LandmassGeneration/Components/TerrainGeneratorComponent.h>
#include <LandmassGeneration/Components/GrassGeneratorComponent.h>

ALandmass::ALandmass()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create the root component
    USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(SceneRoot);

    // Create the terrain generator component
    TerrainGeneratorComponent = CreateDefaultSubobject<UTerrainGeneratorComponent>(TEXT("Terrain Generator Component"));
    TerrainGeneratorComponent->SetupAttachment(SceneRoot);

    GrassGeneratorComponent = CreateDefaultSubobject<UGrassGeneratorComponent>(TEXT("Grass Generator Component"));
    GrassGeneratorComponent->SetupAttachment(SceneRoot);
}

void ALandmass::BeginPlay()
{
    Super::BeginPlay();
    
    RegenerateTerrain();

    // Generate grass after terrain is created
    if (bEnableGrass && GrassGeneratorComponent)
    {
        // We'll defer grass generation slightly to ensure terrain is fully generated
        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(
            TimerHandle,
            [this]() { RegenerateGrass(); },
            0.5f,
            false
        );
    }
}

void ALandmass::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // Apply settings to the terrain component
    if (TerrainGeneratorComponent)
    {
        TerrainGeneratorComponent->MaxTriangleCount = MaxTriangles;
        TerrainGeneratorComponent->bEnableDebugVisualization = bEnableDebugVisualization;
		TerrainGeneratorComponent->bIsEdit = bIsEdit;
    }

    if (GrassGeneratorComponent)
    {
        GrassGeneratorComponent->SetVisibility(bEnableGrass);
    }
}

void ALandmass::RegenerateTerrain()
{
    if (TerrainGeneratorComponent)
    {
        TerrainGeneratorComponent->GenerateTerrain();
    }
}

void ALandmass::RegenerateGrass()
{
    if (bEnableGrass && GrassGeneratorComponent)
    {

    }
}

