// Fill out your copyright notice in the Description page of Project Settings.


#include "Landmass.h"
#include "ProceduralMeshComponent.h"
#include "LandmassGeneration/Components/LandmassComponent.h"

ALandmass::ALandmass()
{
	PrimaryActorTick.bCanEverTick = true;

	LandmassComponent = CreateDefaultSubobject<ULandmassComponent>(TEXT("Landmass Component"));
	SetRootComponent(LandmassComponent);
}

void ALandmass::BeginPlay()
{
	Super::BeginPlay();
}

void ALandmass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

