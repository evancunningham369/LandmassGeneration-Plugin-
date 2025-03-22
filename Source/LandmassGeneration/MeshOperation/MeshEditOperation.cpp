#include "MeshEditOperation.h"

void FMeshEditOperation::AddDensityShaderPass(const uint32& ChunkSize, const FIntVector& ChunkCoords, FRDGBuilder& GraphBuilder, FRDGTextureUAVRef& DensityUAV)
{
	TShaderMapRef<FEditDensityComputeShader> EditDensityShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	uint32 TotalVertices = ChunkSize * ChunkSize * ChunkSize;
	// Use RDG for GPU resource management
	// Create GPU Buffer
	FRDGTextureRef DensityBuffer = CreateTextureBuffer(
		GraphBuilder,
		ChunkSize,
		TEXT("Density Data Buffer")
	);
	// Create an UAV Buffer to enable RW on GPU Buffer
	DensityUAV = GraphBuilder.CreateUAV(FRDGTextureUAVDesc(DensityBuffer));
	// Allocate parameters
	FEditDensityComputeShader::FParameters* EditDensityParams = GraphBuilder.AllocParameters<FEditDensityComputeShader::FParameters>();
	EditDensityParams->DensityMap = DensityUAV;

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
