// Fill out your copyright notice in the Description page of Project Settings.

#include "TerrainGeneratorComponent.h"
#include <LandmassGeneration/Subsystems/LandmassManagerSubsystem.h>
#include "LandmassGeneration/DebugMacros.h"
#include <DynamicMesh/MeshNormals.h>
#include "TerrainChunkComponent.h"

using namespace UE::Geometry;

UTerrainGeneratorComponent::UTerrainGeneratorComponent()
{
}

void UTerrainGeneratorComponent::GenerateTerrain(const FTerrainGenerationParams& Params)
{
    // Store the parameters
    TerrainParams = Params;

    // Create the chunks
    CreateChunks(TerrainParams);

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

    // Request terrain generation
    CurrentGenerationRequestId = ShaderSubsystem->RequestTerrainGeneration(
        TerrainParams,
        TriangleChunks,
        [this](uint32 TriangleCount)
        {
            OnComputeShaderComplete(TriangleCount);
        }
    );
}

void UTerrainGeneratorComponent::CreateChunks(const FTerrainGenerationParams& Params)
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
    int32 ChunksX = 1;
    int32 ChunksY = 1;
    int32 ChunksZ = 1;

    UE_LOG(LogTemp, Warning, TEXT("HARCODED!!!: Creating %d x %d x %d chunks"), ChunksX, ChunksY, ChunksZ);

    // Create chunks
    for (int32 X = 0; X < ChunksX; X++)
    {
        for (int32 Y = 0; Y < ChunksY; Y++)
        {
            for (int32 Z = 0; Z < ChunksZ; Z++)
            {
                FUintVector ChunkCoords(X, Y, Z);
                TriangleChunks.Add(ChunkCoords, TArray<FTriangle>());
                // Create a component for this chunk
                FString ChunkName = FString::Printf(TEXT("Chunk_%d_%d_%d"), X, Y, Z);
                UTerrainChunkComponent* ChunkComponent = NewObject<UTerrainChunkComponent>(GetOwner(), *ChunkName);

                // Set up the component
                ChunkComponent->SetChunkCoords(ChunkCoords);
                ChunkComponent->SetupAttachment(this);
                ChunkComponent->RegisterComponent();

                // Position the chunk in world space
                FVector ChunkPosition(
                    X * ChunkSize * WorldScale,
                    Y * ChunkSize * WorldScale,
                    Z * ChunkSize * WorldScale
                );
                ChunkComponent->SetRelativeLocation(ChunkPosition);
                DRAW_POINT_PERM(ChunkPosition, FColor::Red);
                // Store the chunk info
                FTerrainChunkInfo ChunkInfo;
                ChunkInfo.ChunkCoords = ChunkCoords;
                ChunkInfo.ChunkComponent = ChunkComponent;
                ChunkInfos.Add(ChunkInfo);
            }
        }
    }
}

void UTerrainGeneratorComponent::OnComputeShaderComplete(uint32 TriangleCount)
{
    UE_LOG(LogTemp, Warning, TEXT("Shader Completed!"));
    UE_LOG(LogTemp, Warning, TEXT("Triangle Count: %d"), TriangleCount);

    /*for (uint32 i = 0; i < 5; i++)
    {
        UE_LOG(LogTemp, Warning, TEXT("Data: x: %s y: %s z: %s"), *Triangles[i].Vertex1.ToString(), *Triangles[i].Vertex2.ToString(), *Triangles[i].Vertex3.ToString())
    }*/

    //// Clear the current generation request ID
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