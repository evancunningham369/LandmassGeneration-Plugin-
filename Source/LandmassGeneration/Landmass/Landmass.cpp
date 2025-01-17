// Fill out your copyright notice in the Description page of Project Settings.


#include "Landmass.h"
#include "ProceduralMeshComponent.h"
#include "LandmassGeneration/Components/LandmassComponent.h"

#define DRAW_LINE_PERM(Start, End) DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1.f);
#define DRAW_POINT_PERM(Location, Color) DrawDebugPoint(GetWorld(), Location, 20.f, Color, true, -1.f);


ALandmass::ALandmass()
{
	PrimaryActorTick.bCanEverTick = true;

	LandmassComponent = CreateDefaultSubobject<ULandmassComponent>(TEXT("Landmass Component"));
	SetRootComponent(LandmassComponent);
}

void ALandmass::BeginDestroy()
{
	Super::BeginDestroy();
	UE_LOG(LogTemp, Warning, TEXT("ALandmass is being destroyed!"));
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

