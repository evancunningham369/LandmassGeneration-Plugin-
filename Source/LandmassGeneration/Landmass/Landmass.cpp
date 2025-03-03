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
        TerrainGeneratorComponent->ChunkSize = ChunkSize;
        TerrainGeneratorComponent->MaxTriangleCount = MaxTriangles;
        TerrainGeneratorComponent->bEnableDebugVisualization = bEnableDebugVisualization;
    }
}

#if WITH_EDITOR
void ALandmass::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // Get the name of the property that was changed
    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    // Check if we need to regenerate the terrain
    if (PropertyName == GET_MEMBER_NAME_CHECKED(ALandmass, TerrainQuality) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ALandmass, CustomTerrainWidth) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ALandmass, CustomTerrainHeight) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ALandmass, CustomTerrainDepth) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ALandmass, ChunkSize))
    {
        // Apply settings to the terrain component
        if (TerrainGeneratorComponent)
        {
            TerrainGeneratorComponent->ChunkSize = ChunkSize;
            TerrainGeneratorComponent->MaxTriangleCount = MaxTriangles;
            TerrainGeneratorComponent->bEnableDebugVisualization = bEnableDebugVisualization;
        }
    }
}
#endif

void ALandmass::RegenerateTerrain()
{
    if (TerrainGeneratorComponent)
    {
        FTerrainGenerationParams Params = BuildTerrainParams();
        TerrainGeneratorComponent->GenerateTerrain(Params);
    }
}

FTerrainGenerationParams ALandmass::BuildTerrainParams() const
{
    FTerrainGenerationParams Params;

    // Set the parameters based on the quality preset
    switch (TerrainQuality)
    {
    case ETerrainQuality::Low:
        Params.Width = 32;
        Params.Height = 2;
        Params.Depth = 32;
        break;

    case ETerrainQuality::Medium:
        Params.Width = 64;
        Params.Height = 2;
        Params.Depth = 64;
        break;

    case ETerrainQuality::High:
        Params.Width = 128;
        Params.Height = 2;
        Params.Depth = 128;
        break;

    case ETerrainQuality::Ultra:
        Params.Width = 256;
        Params.Height = 256;
        Params.Depth = 256;
        break;

    case ETerrainQuality::Custom:
        Params.Width = CustomTerrainWidth;
        Params.Height = CustomTerrainHeight;
        Params.Depth = CustomTerrainDepth;
        break;
    }

    // Calculate the total number of vertices
    Params.NumVertices = Params.Width * Params.Height * Params.Depth;

    return Params;
}

