#include "MeshCreationOperation.h"

void FMeshCreationOperation::AddDensityShaderPass(
	TSharedPtr<FTerrainChunkData> ChunkData,
	const uint32& ChunkSize,
	const FIntVector& ChunkCoords,
	FRDGBuilder& GraphBuilder,
	FRDGTextureUAVRef& DensityUAV)
{
	TShaderMapRef<FDensityComputeShader> DensityShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	uint32 TotalVertices = ChunkSize * ChunkSize * ChunkSize;
	// Use RDG for GPU resource management
	// Create GPU Buffer

	if (!ChunkData->DensityMap)
	{
		FRHITextureCreateDesc TextureDesc = FRHITextureCreateDesc::Create3D(
			TEXT("Density Texture"),
			FIntVector(ChunkSize, ChunkSize, ChunkSize),
			PF_R32_FLOAT
		);

		TextureDesc.SetFlags(ETextureCreateFlags::ShaderResource | ETextureCreateFlags::UAV);

		ChunkData->DensityMap = RHICreateTexture(
			TextureDesc
		);
	}

	FRDGTextureRef DensityTextureRDG = GraphBuilder.RegisterExternalTexture(
		CreateRenderTarget(
			ChunkData->DensityMap,
			TEXT("Density Texture")
			));

	DensityUAV = GraphBuilder.CreateUAV(FRDGTextureUAVDesc(DensityTextureRDG));
	

	// Allocate parameters
	FDensityComputeShader::FParameters* DensityParams = GraphBuilder.AllocParameters<FDensityComputeShader::FParameters>();
	DensityParams->DensityMap = DensityUAV;
	DensityParams->ChunkCoords = ChunkCoords;


	// Dispatch the compute shader using FComputeShaderUtils
	// Number of Thread Groups
	const uint32 ThreadGroupSize = 8;

	FIntVector DensityThreadGroups(
		FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize),
		FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize),
		FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize));

	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("Density Shader Pass"),
		DensityShader,
		DensityParams,
		DensityThreadGroups
	);
}