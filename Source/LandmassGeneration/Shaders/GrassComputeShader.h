#pragma once

#include "CoreMinimal.h"
#include "ShaderParameterStruct.h"
#include "RenderResource.h"
#include "RHI.h"
#include "RHIResources.h"

// Instance data for a single grass blade
struct FGrassInstanceData
{
	FMatrix44f Transform;
};

// Parameters for grass generation
struct FGrassShaderParameters
{
	// Terrain information
	FTextureRHIRef TerrainHeightMap;
	FTextureRHIRef TerrainNormalMap;

	// Grass parameters
	float Density;
	FVector MinScale;
	FVector MaxScale;
	float MaxSlope;
	bool bRandomRotation;

	// Grid parameters
	FVector GridOrigin;
	float CellSize;
	int32 GridSizeX;
	int32 GridSizeY;

	// LOD parameters
	FVector CameraPosition;
	float FadeStartDistance;
	float FadeEndDistance;
	float DensityMultiplier;

	// Random seed
	int32 RandomSeed;
};

// Grass placement compute shader
class FGrassPlacementComputeShader : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FGrassPlacementComputeShader);
    SHADER_USE_PARAMETER_STRUCT(FGrassPlacementComputeShader, FGlobalShader);

public:
    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
    }

    static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
    {
        FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
        OutEnvironment.SetDefine(TEXT("COMPUTE_SHADER"), 1);
    }

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_TEXTURE(Texture2D, TerrainHeightMap)
        SHADER_PARAMETER_RDG_TEXTURE(Texture2D, TerrainNormalMap)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FGrassInstanceData>, InstanceBuffer)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<uint32>, CounterBuffer)
        SHADER_PARAMETER(float, Density)
        SHADER_PARAMETER(FVector3f, MinScale)
        SHADER_PARAMETER(FVector3f, MaxScale)
        SHADER_PARAMETER(float, MaxSlope)
        SHADER_PARAMETER(uint32, bRandomRotation)
        SHADER_PARAMETER(FVector3f, GridOrigin)
        SHADER_PARAMETER(float, CellSize)
        SHADER_PARAMETER(uint32, GridSizeX)
        SHADER_PARAMETER(uint32, GridSizeY)
        SHADER_PARAMETER(FVector3f, CameraPosition)
        SHADER_PARAMETER(float, FadeStartDistance)
        SHADER_PARAMETER(float, FadeEndDistance)
        SHADER_PARAMETER(float, DensityMultiplier)
        SHADER_PARAMETER(int32, RandomSeed)
    END_SHADER_PARAMETER_STRUCT()
};

// Utility functions for grass rendering
class FGrassShaderUtils
{
public:
    // Execute the grass placement compute shader
    static void ExecuteGrassPlacementShader(
        FRHICommandListImmediate& RHICmdList,
        const FGrassShaderParameters& Parameters,
        TRefCountPtr<FRDGPooledBuffer> InstancePooledBuffer,
        TRefCountPtr<FRDGPooledBuffer> CounterPooledBuffer,
        FBufferRHIRef InstanceBuffer,
        FUnorderedAccessViewRHIRef InstanceBufferUAV,
        FBufferRHIRef CounterBuffer,
        FUnorderedAccessViewRHIRef CounterBufferUAV
    );
};