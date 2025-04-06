#pragma once

#include "MeshOperation.h"

class FMeshCreationOperation : public FMeshOperation
{
public:
	virtual ~FMeshCreationOperation() = default;
	// Execute the shader operation

	virtual void AddDensityShaderPass(
		TSharedPtr<FTerrainChunkData> ChunkData,
		const uint32& ChunkSize, 
		const FIntVector& ChunkCoords,
		FRDGBuilder& GraphBuilder, 
		FRDGTextureUAVRef& DensityUAV) override;
};