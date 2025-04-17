// Fill out your copyright notice in the Description page of Project Settings.


#include "Landmass.h"
#include "LandmassGeneration/DebugMacros.h"
#include <LandmassGeneration/Components/TerrainGeneratorComponent.h>
#include <LandmassGeneration/Components/GrassGeneratorComponent.h>
#include "LandmassGeneration/Test/Components/SimpleTriangleComponent.h"

ALandmass::ALandmass()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the root component
    USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(SceneRoot);

    // Create the terrain generator component
    TerrainGeneratorComponent = CreateDefaultSubobject<UTerrainGeneratorComponent>(TEXT("Terrain Generator Component"));
    TerrainGeneratorComponent->SetupAttachment(SceneRoot);

    GrassGeneratorComponent = CreateDefaultSubobject<UGrassGeneratorComponent>(TEXT("Grass Generator Component"));
    GrassGeneratorComponent->SetupAttachment(SceneRoot);

    SimpleTriangleComponent = CreateDefaultSubobject<USimpleTriangleComponent>(TEXT("Simple Triangle Component"));
    SimpleTriangleComponent->SetupAttachment(SceneRoot);

    HISMComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMComponent"));
    HISMComponent->SetupAttachment(SceneRoot);

    HISMComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    HISMComponent->SetCastShadow(false);

    HISMComponent->bAffectDistanceFieldLighting = false;
}

void ALandmass::BeginPlay()
{
    Super::BeginPlay();

    GenerateGrass(); // This is using a draw call with a shader to fill grass positions

    //GenerateGrassInstances(); // This is using HISMComponent
    
    //RegenerateTerrain();

    // Generate grass after terrain is created
    /*
    
    if (bEnableGrass && GrassGeneratorComponent)
    {
        // We'll defer grass generation slightly to ensure terrain is fully generated
        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(
            TimerHandle,
            [this]() { RegenerateGrass(); },
            0.5f,
            false
        );
    }
    */
}

void ALandmass::Tick(float DeltaTime)
{
    //UE_LOG(LogTemp, Warning, TEXT("Ticking.."));
    //GenerateGrass();
}

void ALandmass::GenerateGrassInstances()
{
    if (!HISMComponent->GetStaticMesh())
    {
        UE_LOG(LogTemp, Warning, TEXT("GrassSpawner: No Static Mesh assigned to HISMComponent!"));
        return;
    }

    HISMComponent->ClearInstances();

    TArray<FTransform> InstanceTransforms;
    InstanceTransforms.Reserve(NumInstances);

    FVector ActorLocation = GetActorLocation();
    FRandomStream RandStream(FMath::Rand());

    FBox SpawnBox(ActorLocation - SpawnBoxExtents, ActorLocation + SpawnBoxExtents);

    for (int32 i = 0; i < NumInstances; ++i)
    {
        FVector RandPoint = RandStream.RandPointInBox(SpawnBox);
        
        FRotator RandomYawRotator = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
        FTransform InstanceTransform(FQuat::Identity, RandPoint);
        InstanceTransforms.Emplace(InstanceTransform);
    }

    HISMComponent->AddInstances(InstanceTransforms, false);
    UE_LOG(LogTemp, Log, TEXT("GrassSpawner: Added %d grass instances within the spawn volume."), InstanceTransforms.Num());
}

void ALandmass::GenerateGrass()
{
    SimpleTriangleComponent->DrawGrassInstances();
}

void ALandmass::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // Apply settings to the terrain component
    if (TerrainGeneratorComponent)
    {
        TerrainGeneratorComponent->MaxTriangleCount = MaxTriangles;
        TerrainGeneratorComponent->bEnableDebugVisualization = bEnableDebugVisualization;
		TerrainGeneratorComponent->bIsEdit = bIsEdit;
    }
}



void ALandmass::RegenerateTerrain()
{
    if (TerrainGeneratorComponent)
    {
        TerrainGeneratorComponent->GenerateTerrain();
    }
}

void ALandmass::RegenerateGrass()
{

}

