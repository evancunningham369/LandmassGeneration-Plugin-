// Fill out your copyright notice in the Description page of Project Settings.


#include "Landmass.h"
#include "LandmassGeneration/DebugMacros.h"
#include <LandmassGeneration/Components/TerrainGeneratorComponent.h>

ALandmass::ALandmass()
{
	PrimaryActorTick.bCanEverTick = false;
	TerrainGeneratorComponent = CreateDefaultSubobject<UTerrainGeneratorComponent>(TEXT("Terrain Generator Component"));
	SetRootComponent(TerrainGeneratorComponent);
}

void ALandmass::BeginPlay()
{
	Super::BeginPlay();
	if (TerrainGeneratorComponent)
	{
		FTerrainGenerationParams Params;
		Params.Width = 4;
		Params.Depth = 2;
		Params.Height = 2;
		Params.NumVertices = Params.Width * Params.Height * Params.Depth;
		TerrainGeneratorComponent->GenerateTerrain(Params);
	}
}

void ALandmass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

