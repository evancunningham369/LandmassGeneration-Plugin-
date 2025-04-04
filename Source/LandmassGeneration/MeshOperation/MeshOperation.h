#pragma once
#include "LandmassGeneration/Shaders/LandmassComputeShader.h"
#include <LandmassGeneration/LandmassStructs.h>
#include "RenderGraphUtils.h"

struct FMeshOperationParams
{
	virtual ~FMeshOperationParams() = default;
};

struct FMeshCreationParams : public FMeshOperationParams
{

};

struct FMeshEditParams : public FMeshOperationParams
{
	FVector DestructionCenter;
	float DestructionRadius;
};

class FMeshOperation
{
public:
    virtual ~FMeshOperation() = default;

    // Execute the shader operation
    virtual void Execute(
        FRDGBuilder& GraphBuilder,
        FRDGBufferRef& TrianglesOutputBuffer,
        FRDGBufferRef& CounterOutputBuffer,
        const FIntVector& ChunkCoords,
        uint32 ChunkSize,
        TSharedPtr<FTerrainChunkData> ChunkData);

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

    virtual void AddDensityShaderPass(
        const uint32& ChunkSize,
        const FIntVector& ChunkCoords,
        FRDGBuilder& GraphBuilder,
        FRDGTextureUAVRef& DensityUAV) = 0;
};