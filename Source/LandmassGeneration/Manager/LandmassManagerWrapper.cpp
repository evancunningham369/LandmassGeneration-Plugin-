// Fill out your copyright notice in the Description page of Project Settings.


#include "LandmassManagerWrapper.h"
#include "LandmassManager.h"

ALandmassManagerWrapper::ALandmassManagerWrapper()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ALandmassManagerWrapper::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALandmassManagerWrapper::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UWorld* World = GetWorld();
	if (World)
	{
		ULandmassManager::Get()->SpawnChunks(World, SpawnOffset, NumOfChunksX, NumOfChunksY);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("World is invalid"))
	}
}

