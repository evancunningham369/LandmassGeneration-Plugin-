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
        [this](const TArray<FTriangle>& Triangles, uint32 TriangleCount)
        {
            OnComputeShaderComplete(Triangles, TriangleCount);
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
    int32 ChunksX = FMath::CeilToInt((float)Params.Width / ChunkSize);
    int32 ChunksY = FMath::CeilToInt((float)Params.Depth / ChunkSize);
    int32 ChunksZ = FMath::CeilToInt((float)Params.Height / ChunkSize);

    UE_LOG(LogTemp, Warning, TEXT("Creating %d x %d x %d chunks"), ChunksX, ChunksY, ChunksZ);

    // Create chunks
    for (int32 X = 0; X < ChunksX; X++)
    {
        for (int32 Y = 0; Y < ChunksY; Y++)
        {
            for (int32 Z = 0; Z < ChunksZ; Z++)
            {
                FIntVector ChunkCoords(X, Y, Z);

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

void UTerrainGeneratorComponent::OnComputeShaderComplete(const TArray<FTriangle>& Triangles, uint32 TriangleCount)
{
    UE_LOG(LogTemp, Warning, TEXT("Shader Completed!"));
    UE_LOG(LogTemp, Warning, TEXT("Triangle Count: %d"), TriangleCount);

    // Start timing the distribution process
    double StartTime = FPlatformTime::Seconds();

    // Distribute triangles to chunks
    DistributeTrianglesToChunks(Triangles, TriangleCount);

    // Measure and log performance
    double EndTime = FPlatformTime::Seconds();
    UE_LOG(LogTemp, Warning, TEXT("Triangle distribution took %f seconds"), EndTime - StartTime);

    // Clear the current generation request ID
    CurrentGenerationRequestId = INDEX_NONE;
}

void UTerrainGeneratorComponent::DistributeTrianglesToChunks(const TArray<FTriangle>& Triangles, uint32 TriangleCount)
{
    // Create a map to hold triangles for each chunk
    TMap<FIntVector, TArray<FTriangle>> ChunkTriangles;

    // Track how many triangles we process to respect the maximum
    int32 ProcessedTriangles = 0;

    // Process each triangle
    for (int32 i = 0; i < Triangles.Num() && ProcessedTriangles < MaxTriangleCount; i++)
    {
        const FTriangle& Triangle = Triangles[i];

        // Convert to FVector to determine chunk
        FVector Vertex1(Triangle.Vertex1);
        FVector Vertex2(Triangle.Vertex2);
        FVector Vertex3(Triangle.Vertex3);

        // Find the average position to determine which chunk this triangle belongs to
        FVector TriangleCenter = (Vertex1 + Vertex2 + Vertex3) / 3.0f;

        // Get the chunk coordinates for this position
        FIntVector ChunkCoords = GetChunkCoordsForPoint(TriangleCenter);

        // Add the triangle to the appropriate chunk
        if (!ChunkTriangles.Contains(ChunkCoords))
        {
            ChunkTriangles.Add(ChunkCoords, TArray<FTriangle>());
        }
        ChunkTriangles[ChunkCoords].Add(Triangle);

        ProcessedTriangles++;
    }

    // Update each chunk with its triangles
    for (auto& ChunkInfo : ChunkInfos)
    {
        TArray<FTriangle>* ChunkTriangleArray = ChunkTriangles.Find(ChunkInfo.ChunkCoords);

        if (ChunkTriangleArray && ChunkTriangleArray->Num() > 0)
        {
            ChunkInfo.ChunkComponent->UpdateMesh(*ChunkTriangleArray, ChunkTriangleArray->Num());
        }
    }
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