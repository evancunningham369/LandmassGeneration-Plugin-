// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LandmassGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LANDMASSGENERATION_API ALandmassGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void SpawnLandmasses();


};
