// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDefaultPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "LandmassGeneration/Components/LandmassComponent.h"
#include "LandmassGeneration/Landmass/Landmass.h"


AMyDefaultPawn::AMyDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"))

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
	UE_LOG(LogTemp, Warning, TEXT("Click"));

	FHitResult HitResult;
	TraceUnderCrosshairs(HitResult);
	if (HitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit"));

		FVector BoxExtent(ExplosionRadius, ExplosionRadius, 0);
		FCollisionShape BoxShape = FCollisionShape::MakeBox(BoxExtent);


		TArray<FHitResult> HitResults;

		if (GetWorld()->SweepMultiByChannel(
			HitResults,
			HitResult.ImpactPoint,
			HitResult.ImpactPoint,
			FQuat::Identity,
			ECollisionChannel::ECC_Visibility,
			BoxShape
		))
		{
			for (const FHitResult& Hit : HitResults)
			{
				if (ALandmass* Landmass = Cast<ALandmass>(Hit.GetActor()))
				{
					if (Landmass->GetLandmassComponent())
					{
						Landmass->GetLandmassComponent()->OnHit(Hit, ExplosionRadius);
					}
				}
			}
		}
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, BoxExtent, FQuat::Identity, FColor::Red, false, 2.0f);
	}
}

void AMyDefaultPawn::TraceUnderCrosshairs(FHitResult& HitResult)
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
		DrawLine(Start, End);

		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility
		);

		if (HitResult.bBlockingHit)
		{
			DrawSphere(HitResult.ImpactPoint, FColor::Black);
		}
		else
		{
			HitResult.ImpactPoint = End;
			DrawSphere(End, FColor::Blue);
		}
	}
}

void AMyDefaultPawn::DrawSphere(FVector Location, FColor Color)
{
	DrawDebugSphere(
		GetWorld(),
		Location,
		20.f,
		12,
		Color,
		false,
		5.f
	);
}

void AMyDefaultPawn::DrawLine(FVector Start, FVector End)
{
	DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor::Red,
		false,
		5.f
	);
}
