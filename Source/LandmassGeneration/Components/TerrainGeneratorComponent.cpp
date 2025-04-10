// Fill out your copyright notice in the Description page of Project Settings.

#include "TerrainGeneratorComponent.h"
#include <LandmassGeneration/Subsystems/LandmassManagerSubsystem.h>
#include "LandmassGeneration/DebugMacros.h"
#include <DynamicMesh/MeshNormals.h>
#include "TerrainChunkComponent.h"
#include <LandmassGeneration/MeshOperation/MeshOperation.h>
#include <LandmassGeneration/MeshOperation/MeshCreationOperation.h>
#include <LandmassGeneration/MeshOperation/MeshEditOperation.h>

using namespace UE::Geometry;

UTerrainGeneratorComponent::UTerrainGeneratorComponent()
{
}

void UTerrainGeneratorComponent::GenerateTerrain()
{

    // Create the chunks
    CreateChunks();

    // Get the subsystem
    if (!ShaderSubsystem)
    {
        ShaderSubsystem = GetWorld()->GetSubsystem<ULandmassManagerSubsystem>();
    }

    // Cancel any existing requests
    if (CurrentGenerationRequestId != INDEX_NONE)
    {
        ShaderSubsystem->CancelRequest(CurrentGenerationRequestId);
        CurrentGenerationRequestId = INDEX_NONE;
    }

    TSharedPtr<FMeshOperation> MeshOperation;

     MeshOperation = MakeShared<FMeshCreationOperation>();

    // Request terrain generation
    CurrentGenerationRequestId = ShaderSubsystem->RequestTerrainGeneration(
        ChunkInfos,
		ChunkSize,
		ChunksX * ChunksY * ChunksZ,
        MeshOperation,
        [this]()
        {
            OnComputeShaderComplete();
        }
    );

    //ShaderSubsystem->TestShader(ChunkInfos, ChunkSize);
}

void UTerrainGeneratorComponent::UpdateTerrain(UTerrainChunkComponent& ChunkComponent, FVector& HitLocation, float DestructionRadius)
{
	if (!ShaderSubsystem)
	{
		ShaderSubsystem = GetWorld()->GetSubsystem<ULandmassManagerSubsystem>();
	}

	TSharedPtr<FMeshEditOperation> MeshOperation = MakeShared<FMeshEditOperation>();
	FVector ScaledHitLocation = HitLocation / 100;
    // Debug location
	UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *ScaledHitLocation.ToString());

	FMeshEditParams EditParams;
	EditParams.DestructionCenter = ScaledHitLocation;
	EditParams.DestructionRadius = DestructionRadius;

	MeshOperation->SetEditParams(EditParams);

	ShaderSubsystem->RequestTerrainModification(
		ChunkComponent,
		MeshOperation,
		[this, &ChunkComponent]()
		{
			OnEditComputeShaderComplete(ChunkComponent);
		}
	);
}

void UTerrainGeneratorComponent::OnEditComputeShaderComplete(UTerrainChunkComponent& TerrainChunk)
{
    UE_LOG(LogTemp, Warning, TEXT("Edit Shader Completed!"));
    UE_LOG(LogTemp, Warning, TEXT("Triangle Count: %d"), TerrainChunk.GetChunkData()->TriangleCount);
	FTerrainChunkDataPtr ChunkData = TerrainChunk.GetChunkData();

    TerrainChunk.EditChunkMesh(ChunkData->Triangles);
}

void UTerrainGeneratorComponent::GetTerrainChunks(TArray<UTerrainChunkComponent*>& OutChunks) const
{
    OutChunks.Empty();
    for (const FTerrainChunkInfo& ChunkInfo : ChunkInfos)
    {
        if (ChunkInfo.ChunkComponent)
        {
            OutChunks.Add(ChunkInfo.ChunkComponent);
        }
    }
}

void UTerrainGeneratorComponent::CreateChunks()
{
    // Clear existing chunks
    for (FTerrainChunkInfo& ChunkInfo : ChunkInfos)
    {
        if (ChunkInfo.ChunkComponent)
        {
            ChunkInfo.ChunkComponent->DestroyComponent();
        }
    }
    ChunkInfos.Empty();
    
    // Calculate how many chunks we need in each dimension

	FIntVector ChunkCount(ChunksX, ChunksY, ChunksZ);

    UE_LOG(LogTemp, Warning, TEXT("Creating %d x %d x %d chunks"), ChunksX, ChunksY, ChunksZ);

    // Create chunks
    for (int32 X = 0; X < ChunksX; X++)
    {
        for (int32 Y = 0; Y < ChunksY; Y++)
        {
            for (int32 Z = 0; Z < ChunksZ; Z++)
            {
                FIntVector ChunkCoords(X, Y, Z);
                
				TSharedPtr<FTerrainChunkData> ChunkData = MakeShared<FTerrainChunkData>();

                // Create a component for this chunk
                FString ChunkName = FString::Printf(TEXT("Chunk_%d_%d_%d"), X, Y, Z);
                UTerrainChunkComponent* ChunkComponent = NewObject<UTerrainChunkComponent>(GetOwner(), *ChunkName);

                // Set up the component
                ChunkComponent->SetChunkCoords(ChunkCoords);
				ChunkComponent->SetChunkData(ChunkData);
                ChunkComponent->SetupAttachment(this);
                ChunkComponent->RegisterComponent();

                // Position the chunk in world space
                FVector ChunkPosition(
                    X * ChunkSize,
                    Y * ChunkSize,
                    Z * ChunkSize
                );
                ChunkComponent->SetRelativeLocation(ChunkPosition);
                // Store the chunk info
                FTerrainChunkInfo ChunkInfo;
                ChunkInfo.ChunkCoords = ChunkCoords;
                ChunkInfo.ChunkComponent = ChunkComponent;
				ChunkInfo.ChunkData = ChunkData;
                ChunkInfos.Add(ChunkInfo);
            }
        }
    }
}

void UTerrainGeneratorComponent::OnComputeShaderComplete()
{
    UE_LOG(LogTemp, Warning, TEXT("Shader Completed!"));

    // Update all chunks with their respective triangles
    for (FTerrainChunkInfo& ChunkInfo : ChunkInfos)
    {
        if (!ChunkInfo.ChunkData.IsValid() || !ChunkInfo.ChunkComponent)
        {
            continue;
        }

        // Access the shared data
        const TSharedPtr<FTerrainChunkData> ChunkData = ChunkInfo.ChunkData;

        if (ChunkData->bIsProcessed)
        {
            // Update the mesh with triangles from shared data
            ChunkInfo.ChunkComponent->UpdateMeshFromSharedData();

            // Debug visualization if enabled
            if (bEnableDebugVisualization)
            {
                // Debug Log the Triangles
            }
        }
    }
    // Clear the current generation request ID
    CurrentGenerationRequestId = INDEX_NONE;
}

FIntVector UTerrainGeneratorComponent::GetChunkCoordsForPoint(const FVector& Point) const
{
    // Convert point to chunk coordinates
    int32 X = FMath::FloorToInt(Point.X / ChunkSize);
    int32 Y = FMath::FloorToInt(Point.Y / ChunkSize);
    int32 Z = FMath::FloorToInt(Point.Z / ChunkSize);

    return FIntVector(X, Y, Z);
}

void UTerrainGeneratorComponent::BeginDestroy()
{
    if (CurrentGenerationRequestId != INDEX_NONE && ShaderSubsystem)
    {
        ShaderSubsystem->CancelRequest(CurrentGenerationRequestId);
        CurrentGenerationRequestId = INDEX_NONE;
    }

    Super::BeginDestroy();
}

void UTerrainGeneratorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (CurrentGenerationRequestId != INDEX_NONE && ShaderSubsystem)
    {
        ShaderSubsystem->CancelRequest(CurrentGenerationRequestId);
        CurrentGenerationRequestId = INDEX_NONE;
    }

    Super::EndPlay(EndPlayReason);
}