// Fill out your copyright notice in the Description page of Project Settings.


#include "Landmass.h"
#include "ProceduralMeshComponent.h"
#include "LandmassGeneration/Components/LandmassComponent.h"

ALandmass::ALandmass()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	LandmassComponent = CreateDefaultSubobject<ULandmassComponent>(TEXT("Landmass Component"));
	LandmassComponent->SetupAttachment(RootComponent);
}

void ALandmass::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0.f, 0.f, 0.f));
}

void ALandmass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

