// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDefaultPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <Kismet/GameplayStatics.h>
#include "LandmassGeneration/Components/LandmassComponent.h"
#include "LandmassGeneration/Landmass/Landmass.h"
#include "LandmassGeneration/Manager/LandmassManager.h"
#include "LandmassGeneration/DebugMacros.h"
#include "LandmassGeneration/Manager/LandmassManagerWrapper.h"

AMyDefaultPawn::AMyDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Begin Play"))

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}


}


void AMyDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AMyDefaultPawn::Click);
	}
}

void AMyDefaultPawn::Click(const FInputActionValue& Value)
{
	TraceUnderCrosshairs();
}

void AMyDefaultPawn::TraceUnderCrosshairs()
{
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	);
	if (bScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;

		FVector End = Start + CrosshairWorldDirection * EndDistance;
		FHitResult HitResult;

		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility
		);

		if (HitResult.bBlockingHit)
		{
			DRAW_LINE(Start, HitResult.ImpactPoint);
			DRAW_SPHERE(HitResult.ImpactPoint, FColor::Black);
			if (ALandmassManagerWrapper* LandmassManagerWrapper = Cast<ALandmassManagerWrapper>(HitResult.GetActor()))
			{
				LandmassManagerWrapper->ReCreateMesh(HitResult.Location);
			}
		}
		else
		{
			DRAW_LINE(Start, End);
			DRAW_SPHERE(End, FColor::Black);
			HitResult.ImpactPoint = End;
		}
	}
}
