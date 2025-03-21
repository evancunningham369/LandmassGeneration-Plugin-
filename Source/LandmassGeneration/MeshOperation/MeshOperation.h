#pragma once

#include "CoreMinimal.h"
#include "LandmassGeneration/LandmassStructs.h"
#include "RenderGraphBuilder.h"

class FMeshOperation
{
public:
    virtual ~FMeshOperation() = default;

    // Execute the shader operation
    virtual void Execute(
        FRDGBuilder& GraphBuilder,
        FRDGBufferRef& TrianglesOutputBuffer,
        const FIntVector& ChunkCoords,
        uint32 ChunkSize,
        TSharedPtr<FTerrainChunkData> ChunkData) = 0;

protected:
    FRDGBufferRef CreateEmptyBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements)
    {
        return GraphBuilder.CreateBuffer(
            FRDGBufferDesc::CreateStructuredDesc(SizeOfElement, NumOfElements),
            TEXT("OutputBuffer")
        );
    };
    FRDGTextureRef CreateTextureBuffer(FRDGBuilder& GraphBuilder, const uint32& ChunkSize, const TCHAR* DebugName)
    {
        FRDGTextureDesc Desc = FRDGTextureDesc::Create3D(
            FIntVector(ChunkSize, ChunkSize, ChunkSize),
            PF_R32_FLOAT,
            FClearValueBinding::None,
            TexCreate_UAV | TexCreate_ShaderResource
        );

        FRDGTexture* Texture = GraphBuilder.CreateTexture(
            Desc,
            DebugName
        );

        return Texture;
    };
};