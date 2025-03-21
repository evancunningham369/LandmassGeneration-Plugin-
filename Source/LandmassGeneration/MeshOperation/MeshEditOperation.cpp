
#include "MeshEditOperation.h"
#include <LandmassGeneration/Shaders/LandmassComputeShader.h>
#include <RenderGraphUtils.h>

void FMeshEditOperation::Execute(FRDGBuilder& GraphBuilder, FRDGBufferRef& TrianglesOutputBuffer, const FIntVector& ChunkCoords, uint32 ChunkSize, TSharedPtr<FTerrainChunkData> ChunkData)
{
	uint32 NumTrianglesPerChunk = ChunkData->TriangleCount;

	FRDGTextureUAVRef DensityUAV;
	AddEditDensityCubesShaderPass(ChunkSize, ChunkCoords, GraphBuilder, DensityUAV);

	// Marching cubes pass
	TrianglesOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(FTriangle), NumTrianglesPerChunk);
	FRDGBufferRef CounterOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(uint32), 1);

	FRDGBufferUAVRef TrianglesOutputBufferUAV = GraphBuilder.CreateUAV(TrianglesOutputBuffer);
	FRDGBufferUAVRef CounterOutputBufferUAV = GraphBuilder.CreateUAV(CounterOutputBuffer, PF_R32_UINT);

	AddClearUAVPass(GraphBuilder, CounterOutputBufferUAV, 0);

	TShaderMapRef<FMarchingCubesShader> MarchingCubesShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	FMarchingCubesShader::FParameters* MarchingCubesParams = GraphBuilder.AllocParameters<FMarchingCubesShader::FParameters>();
	MarchingCubesParams->Triangles = TrianglesOutputBufferUAV;
	MarchingCubesParams->DensityMap = DensityUAV;
	MarchingCubesParams->Counter = CounterOutputBufferUAV;
	MarchingCubesParams->VolumeSize = FIntVector(ChunkSize, ChunkSize, 2);
	MarchingCubesParams->ChunkCoords = ChunkCoords;
	MarchingCubesParams->ChunkSize = ChunkSize;

	const uint32 ThreadGroupSize = 8;

	FIntVector MarchingCubesThreadGroups(
		FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize),
		FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize),
		FMath::DivideAndRoundUp(ChunkSize, ThreadGroupSize));


	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("Marching Cubes Shader Pass"),
		MarchingCubesShader,
		MarchingCubesParams,
		MarchingCubesThreadGroups
	);
}

void FMeshEditOperation::AddEditDensityCubesShaderPass(const uint32& ChunkSize, const FIntVector& ChunkCoords, FRDGBuilder& GraphBuilder, FRDGTextureUAVRef& DensityUAV)
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
