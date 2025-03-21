#pragma once

#include "MeshOperation.h"

class FMeshCreationOperation : public FMeshOperation
{
public:
	virtual ~FMeshCreationOperation() = default;
	// Execute the shader operation
	virtual void Execute(
		FRDGBuilder& GraphBuilder,
		FRDGBufferRef& TrianglesOutputBuffer,
		const FIntVector& ChunkCoords,
		uint32 ChunkSize,
		TSharedPtr<FTerrainChunkData> ChunkData) override;

	void AddDensityCubesShaderPass(
		const uint32& ChunkSize, 
		const FIntVector& ChunkCoords,
		FRDGBuilder& GraphBuilder, 
		FRDGTextureUAVRef& DensityUAV);
};