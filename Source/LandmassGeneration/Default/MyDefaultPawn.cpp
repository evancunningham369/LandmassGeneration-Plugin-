// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDefaultPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <Kismet/GameplayStatics.h>
#include "LandmassGeneration/Landmass/Landmass.h"
#include "LandmassGeneration/DebugMacros.h"
#include <LandmassGeneration/Components/TerrainGeneratorComponent.h>
#include <LandmassGeneration/Components/TerrainChunkComponent.h>

#define LANDMASS_CHANNEL ECC_GameTraceChannel1

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
			ECollisionChannel::ECC_GameTraceChannel1
		);

		if (HitResult.bBlockingHit)
		{
			//CalculateHit(HitResult);
			DRAW_SPHERE(HitResult.ImpactPoint, FColor::Black);
			DRAW_LINE(Start, HitResult.ImpactPoint);
			if (UTerrainChunkComponent* TerrainChunk = Cast<UTerrainChunkComponent>(HitResult.GetComponent()))
			{
				UE_LOG(LogTemp, Warning, TEXT("Terrain Chunk Found!"));
				if (UTerrainGeneratorComponent* TerrainGeneratorComponent = Cast<UTerrainGeneratorComponent>(TerrainChunk->GetAttachParent()))
				{
					UE_LOG(LogTemp, Warning, TEXT("Terrain Generator Component Found!"));
					TerrainGeneratorComponent->UpdateTerrain(*TerrainChunk);
				}
			}
		}
		else
		{
			HitResult.ImpactPoint = End;
		}
	}
}

void AMyDefaultPawn::CalculateHit(const FHitResult& HitResult)
{
	FVector BoxExtent(ExplosionRadius, ExplosionRadius, ExplosionRadius);
	FCollisionShape BoxShape = FCollisionShape::MakeBox(BoxExtent);
	float ExplosionRadiusCopy = ExplosionRadius;

	TArray<FHitResult> HitResults;
	TSet<UTerrainGeneratorComponent*> UniqueLandmasses;

	FVector HitLocation = HitResult.ImpactPoint;
	if (GetWorld()->SweepMultiByChannel(
		HitResults,
		HitResult.ImpactPoint,
		HitResult.ImpactPoint,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		BoxShape
	))
	{
		for (const FHitResult& Result : HitResults)
		{
			// To-Do
		}
	}
}
