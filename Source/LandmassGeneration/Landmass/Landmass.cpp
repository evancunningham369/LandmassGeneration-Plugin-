// Fill out your copyright notice in the Description page of Project Settings.


#include "Landmass.h"
#include "LandmassGeneration/Components/LandmassComponent.h"
#include "LandmassGeneration/DebugMacros.h"

ALandmass::ALandmass()
{
	PrimaryActorTick.bCanEverTick = false;

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

ULandmassComponent* ALandmass::GetLandmassComponent()
{
	if (LandmassComponent)
	{
		return LandmassComponent;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Landmass Component!"))
	}
	return nullptr;
}

