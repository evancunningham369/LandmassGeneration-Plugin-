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

	float SpawnOffset = 3100.f;

	UPROPERTY(EditAnywhere)
	float NumOfChunks = 2;
protected:
	virtual void BeginPlay() override;

};
