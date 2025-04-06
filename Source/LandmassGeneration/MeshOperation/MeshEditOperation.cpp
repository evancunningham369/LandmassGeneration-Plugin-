#include "MeshEditOperation.h"

void FMeshEditOperation::AddDensityShaderPass(
	TSharedPtr<FTerrainChunkData> ChunkData,
	const uint32& ChunkSize, 
	const FIntVector& ChunkCoords, 
	FRDGBuilder& GraphBuilder, 
	FRDGTextureUAVRef& DensityUAV)
{
	TShaderMapRef<FEditDensityComputeShader> EditDensityShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	uint32 TotalVertices = ChunkSize * ChunkSize * ChunkSize;
	// Use RDG for GPU resource management

	FRDGTextureRef DensityTextureRDG = GraphBuilder.RegisterExternalTexture(
		CreateRenderTarget(
			ChunkData->DensityMap,
			TEXT("Density Texture")
		));

	FVector3f TestDestructionCenter = FVector3f(ChunkSize / 2, 0, ChunkSize / 2);

	
	// Create an UAV Buffer to enable RW on GPU Buffer
	DensityUAV = GraphBuilder.CreateUAV(FRDGTextureUAVDesc(DensityTextureRDG));
	// Allocate parameters
	FEditDensityComputeShader::FParameters* EditDensityParams = GraphBuilder.AllocParameters<FEditDensityComputeShader::FParameters>();
	EditDensityParams->DensityMap = DensityUAV;
	EditDensityParams->DestructionCenter = (FVector3f)EditParams.DestructionCenter;
	EditDensityParams->DestructionRadius = EditParams.DestructionRadius;

	// Number of Thread Groups
	const uint32 ThreadGroupSize = 8;

	FIntVector EditDensityThreadGroups(
		FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize),
		FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize),
		FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize));

	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("Edit Density Shader Pass"),
		EditDensityShader,
		EditDensityParams,
		EditDensityThreadGroups
	);
}
