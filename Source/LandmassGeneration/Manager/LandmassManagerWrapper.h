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

	UPROPERTY(EditAnywhere)
	UMaterialInstance* TerrainMaterial;

	int32 TerrainWidth = 10;

	int32 TerrainHeight = 10;

	UPROPERTY(EditAnywhere)
	int32 NumOfChunksX = 0;

	UPROPERTY(EditAnywhere)
	int32 NumOfChunksY = 0;

	int32 NumOfChunksZ = 3;

protected:
	virtual void BeginPlay() override;


	virtual void PostInitializeComponents() override;

};
