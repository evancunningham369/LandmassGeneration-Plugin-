// Fill out your copyright notice in the Description page of Project Settings.


#include "Landmass.h"
#include "LandmassGeneration/DebugMacros.h"
#include <LandmassGeneration/Components/TerrainGeneratorComponent.h>

ALandmass::ALandmass()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create the root component
    USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(SceneRoot);

    // Create the terrain generator component
    TerrainGeneratorComponent = CreateDefaultSubobject<UTerrainGeneratorComponent>(TEXT("Terrain Generator Component"));
    TerrainGeneratorComponent->SetupAttachment(SceneRoot);
}

void ALandmass::BeginPlay()
{
    Super::BeginPlay();
    
    RegenerateTerrain();
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
}

void ALandmass::RegenerateTerrain()
{
    if (TerrainGeneratorComponent)
    {
        TerrainGeneratorComponent->GenerateTerrain();
    }
}

