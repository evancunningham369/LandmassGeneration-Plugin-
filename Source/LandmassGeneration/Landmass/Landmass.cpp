// Fill out your copyright notice in the Description page of Project Settings.


#include "Landmass.h"
#include "ProceduralMeshComponent.h"
#include "LandmassGeneration/Components/LandmassComponent.h"

ALandmass::ALandmass()
{
	PrimaryActorTick.bCanEverTick = true;
	LandmassComponent = CreateDefaultSubobject<ULandmassComponent>(TEXT("Landmass Component"));
}

void ALandmass::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0.f, 0.f, 0.f));
}

void ALandmass::OnHit(const FHitResult& HitResult, float explosionRadius)
{
	FVector HitLocation = HitResult.Location;
	if (LandmassComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Landmass Component is valid"));

		LandmassComponent->RemoveMesh(HitLocation, explosionRadius);
	}
}

void ALandmass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

