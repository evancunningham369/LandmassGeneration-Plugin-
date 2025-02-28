#pragma once

struct FTriangle
{
    FVector3f Vertex1;
    FVector3f Vertex2;
    FVector3f Vertex3;
};


struct FTerrainGenerationParams
{
    uint32 Width;
    uint32 Height;
    uint32 Depth;
    uint32 NumVertices;
};

