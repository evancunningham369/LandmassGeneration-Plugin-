#include "ShaderParameterStruct.h"
#include "LandmassGeneration/LandmassStructs.h"

class FDensityComputeShader : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FDensityComputeShader);
    SHADER_USE_PARAMETER_STRUCT(FDensityComputeShader, FGlobalShader)

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
        SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture3D<float>, DensityMap)
    END_SHADER_PARAMETER_STRUCT()
};

class FMarchingCubesShader : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FMarchingCubesShader);
    SHADER_USE_PARAMETER_STRUCT(FMarchingCubesShader, FGlobalShader)

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
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FTriangle>, Triangles)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<uint32>, Counter)
        SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture3D<float>, DensityMap)
    END_SHADER_PARAMETER_STRUCT()

};

