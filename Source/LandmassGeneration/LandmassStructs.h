#pragma once
#include "CoreMinimal.h"
#include "LandmassStructs.generated.h"

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

USTRUCT()
struct FTerrainGenerationParams
{
    GENERATED_BODY()

    uint32 Width;
    uint32 Height;
    uint32 Depth;
    uint32 NumVertices;
};

