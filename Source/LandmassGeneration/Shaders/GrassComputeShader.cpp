#include "GrassComputeShader.h"
#include "ShaderParameterUtils.h"
#include "RenderGraphBuilder.h"
#include "RenderGraphUtils.h"
#include "RHIStaticStates.h"
#include "ShaderParameterStruct.h"
#include "RHIResources.h"
#include "RenderResource.h"
#include "Containers/DynamicRHIResourceArray.h"
#include "RenderGraphUtils.h"

// Register the shader
IMPLEMENT_GLOBAL_SHADER(FGrassPlacementComputeShader, "/Project/GrassComputeShader.usf", "PlaceGrass", SF_Compute);

void FGrassShaderUtils::ExecuteGrassPlacementShader(
	FRHICommandListImmediate& RHICmdList, 
	const FGrassShaderParameters& Parameters, 
	TRefCountPtr<FRDGPooledBuffer> InstancePooledBuffer,
	TRefCountPtr<FRDGPooledBuffer> CounterPooledBuffer,
	FBufferRHIRef InstanceBuffer, 
	FUnorderedAccessViewRHIRef InstanceBufferUAV, 
	FBufferRHIRef CounterBuffer, 
	FUnorderedAccessViewRHIRef CounterBufferUAV)
{
	// Create a render graph builder
	FRDGBuilder GraphBuilder(RHICmdList);

	// Register external resources with the render graph
	FRDGTextureRef HeightMapTexture = GraphBuilder.RegisterExternalTexture(
		CreateRenderTarget(Parameters.TerrainHeightMap, TEXT("Terrain Height Map")));

	FRDGTextureRef NormalMapTexture = Parameters.TerrainNormalMap ?
		GraphBuilder.RegisterExternalTexture(CreateRenderTarget(Parameters.TerrainNormalMap, TEXT("Terrain Normal Map")))
		: nullptr;

	// Reuse existing buffer
	FRDGBufferRef InstanceBufferRDG = GraphBuilder.RegisterExternalBuffer(InstancePooledBuffer);
	FRDGBufferRef CounterBufferRDG = GraphBuilder.RegisterExternalBuffer(CounterPooledBuffer);

	// Create the Uniformed Access Views
	FRDGBufferUAVRef InstanceBufferUAVRDG = GraphBuilder.CreateUAV(InstanceBufferRDG);
	FRDGBufferUAVRef CounterBufferUAVRDG = GraphBuilder.CreateUAV(CounterBufferRDG);

	// Clear the counter buffer
	AddClearUAVPass(GraphBuilder, CounterBufferUAVRDG, 0);

	// Get shader reference
	TShaderMapRef<FGrassPlacementComputeShader> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	// Allocate shader parameters
	FGrassPlacementComputeShader::FParameters* PassParameters = GraphBuilder.AllocParameters<FGrassPlacementComputeShader::FParameters>();

	// Setup shader parameters
    PassParameters->TerrainHeightMap = HeightMapTexture;
    PassParameters->TerrainNormalMap = NormalMapTexture;
    PassParameters->InstanceBuffer = InstanceBufferUAVRDG;
    PassParameters->CounterBuffer = CounterBufferUAVRDG;
    PassParameters->Density = Parameters.Density;
    PassParameters->MinScale = FVector3f(Parameters.MinScale);
    PassParameters->MaxScale = FVector3f(Parameters.MaxScale);
    PassParameters->MaxSlope = Parameters.MaxSlope;
    PassParameters->bRandomRotation = Parameters.bRandomRotation ? 1 : 0;
    PassParameters->GridOrigin = FVector3f(Parameters.GridOrigin);
    PassParameters->CellSize = Parameters.CellSize;
    PassParameters->GridSizeX = Parameters.GridSizeX;
    PassParameters->GridSizeY = Parameters.GridSizeY;
    PassParameters->CameraPosition = FVector3f(Parameters.CameraPosition);
    PassParameters->FadeStartDistance = Parameters.FadeStartDistance;
    PassParameters->FadeEndDistance = Parameters.FadeEndDistance;
    PassParameters->DensityMultiplier = Parameters.DensityMultiplier;
    PassParameters->RandomSeed = Parameters.RandomSeed;

    // Calculate dispatch size
    const uint32 ThreadGroupSize = 8;
    FIntVector DispatchCount(
        FMath::DivideAndRoundUp((int32)Parameters.GridSizeX, (int32)ThreadGroupSize),
        FMath::DivideAndRoundUp((int32)Parameters.GridSizeY, (int32)ThreadGroupSize),
        1
    );

    // Add compute shader pass to the graph
    FComputeShaderUtils::AddPass(
        GraphBuilder,
        RDG_EVENT_NAME("Grass Placement Compute"),
        ComputeShader,
        PassParameters,
        DispatchCount
    );

    // Execute the render graph
    GraphBuilder.Execute();
}
