// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Landmass.generated.h"

UCLASS()
class LANDMASSGENERATION_API ALandmass : public AActor
{
	GENERATED_BODY()
	
public:	
	ALandmass();

	class UTerrainGeneratorComponent* TerrainGeneratorComponent;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
