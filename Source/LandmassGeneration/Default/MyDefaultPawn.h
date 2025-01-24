// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "InputActionValue.h"
#include "MyDefaultPawn.generated.h"

/**
 * 
 */
UCLASS()
class LANDMASSGENERATION_API AMyDefaultPawn : public ADefaultPawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ClickAction;

public:
	AMyDefaultPawn();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float EndDistance = 20000.f;

	UPROPERTY(EditAnywhere)
	float ExplosionRadius = 200.f;

protected:
	virtual void BeginPlay() override;
private:

	void Click(const FInputActionValue& Value);

	void TraceUnderCrosshairs();
};
