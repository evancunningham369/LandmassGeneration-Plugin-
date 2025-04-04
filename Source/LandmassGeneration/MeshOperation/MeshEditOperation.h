#pragma once

#include "MeshOperation.h"

class FMeshEditOperation : public FMeshOperation
{
public:
	virtual ~FMeshEditOperation() = default;
	// Execute the shader operation

	virtual void AddDensityShaderPass(
		const uint32& ChunkSize,
		const FIntVector& ChunkCoords,
		FRDGBuilder& GraphBuilder,
		FRDGTextureUAVRef& DensityUAV) override;

	void SetEditParams(const FMeshEditParams& InParams)
	{
		EditParams = InParams;
	}

private:
	FMeshEditParams EditParams;
};