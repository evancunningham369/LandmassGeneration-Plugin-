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
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class ULandmassComponent* LandmassComponent;

	FORCEINLINE ULandmassComponent* GetLandmassComponent() const { return LandmassComponent; }
};
