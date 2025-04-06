#include "MeshOperation.h"

void FMeshOperation::Execute(
    FRDGBuilder& GraphBuilder, 
    FRDGBufferRef& TrianglesOutputBuffer,
	FRDGBufferRef& CounterOutputBuffer,
    const FIntVector& ChunkCoords, 
    uint32 ChunkSize, 
    TSharedPtr<FTerrainChunkData> ChunkData)
{
    uint32 NumTrianglesPerChunk = ChunkData->TriangleCount;

    // Call the strategy-specific density shader pass
    FRDGTextureUAVRef DensityUAV;

    AddDensityShaderPass(ChunkData, ChunkSize, ChunkCoords, GraphBuilder, DensityUAV);

    // Marching cubes pass - common to all operations
    TrianglesOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(FTriangle), NumTrianglesPerChunk);
    CounterOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(uint32), 1);

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
