// Fill out your copyright notice in the Description page of Project Settings.


#include "LandmassGameMode.h"
#include "LandmassGeneration/Subsystems/LandmassManagerSubsystem.h"

void ALandmassGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWorld* World = GetWorld())
	{
		if (ULandmassManagerSubsystem* LandmassSubsystem = World->GetSubsystem<ULandmassManagerSubsystem>())
		{
			//LandmassSubsystem->SpawnChunks();
			LandmassSubsystem->CreateMap();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to get subsystem"))
		}
	}
}
