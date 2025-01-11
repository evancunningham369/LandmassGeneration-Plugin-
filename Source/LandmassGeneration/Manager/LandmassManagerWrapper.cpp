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
	
	UWorld* World = GetWorld();
	if (World)
	{
		ULandmassManager::Get()->SpawnChunks(World, SpawnOffset, NumOfChunks);
	}
}

