// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "LandmassManagerWrapper.h"
#include "LandmassManager.h"
#include "LandmassGeneration/Compute/LandmassCompute.h"

#define TRIANGULATION_TABLE_SIZE 4096

ALandmassManagerWrapper::ALandmassManagerWrapper()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

void ALandmassManagerWrapper::BeginPlay()
{
	Super::BeginPlay();
	FMyComputeShaderWrapper::Get().Dispatch(sizeof(int32), 10);
}

void ALandmassManagerWrapper::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UWorld* World = GetWorld();
	if (World)
	{
		if (NumOfChunksX <= 0 || NumOfChunksY <= 0) return;
		ULandmassManager::Get()->SpawnChunks(World, TerrainWidth, TerrainHeight, NumOfChunksX, NumOfChunksY, NumOfChunksZ ,TerrainMaterial);
		//ULandmassManager::Get()->SpawnChunk(World, TerrainWidth, TerrainHeight, TerrainMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("World is invalid"))
	}
}


