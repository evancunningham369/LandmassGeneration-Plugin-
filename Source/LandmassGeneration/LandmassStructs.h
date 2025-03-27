#pragma once
#include "CoreMinimal.h"
#include "LandmassStructs.generated.h"

USTRUCT()

struct FTerrainChunkData
{
    GENERATED_BODY()

    TArray<FTriangle> Triangles;
    int32 TriangleCount = 0;
    bool bIsProcessed = false;
};

typedef TSharedPtr<FTerrainChunkData> FTerrainChunkDataPtr;
typedef TSharedRef<FTerrainChunkData> FTerrainChunkDataRef;

USTRUCT()
struct FTriangle
{
    GENERATED_BODY()

    UPROPERTY()
    FVector3f Vertex1;
    UPROPERTY()
    FVector3f Vertex2;
    UPROPERTY()
    FVector3f Vertex3;
};

