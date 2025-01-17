// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandmassManagerWrapper.generated.h"

UCLASS()
class LANDMASSGENERATION_API ALandmassManagerWrapper : public AActor
{
	GENERATED_BODY()
	
public:	
	ALandmassManagerWrapper();

	float SpawnOffset = 2900.f;

	int32 NumOfChunksX = 2;

	int32 NumOfChunksY = 3;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

};
