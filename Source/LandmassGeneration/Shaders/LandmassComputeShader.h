#include "ShaderParameterStruct.h"

class FMyComputeShader : public FGlobalShader
{
public:
    DECLARE_GLOBAL_SHADER(FMyComputeShader);
    SHADER_USE_PARAMETER_STRUCT(FMyComputeShader, FGlobalShader)

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<int>, OutputBufferUAV)
        SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<int>, TriangleTableBufferSRV)
    END_SHADER_PARAMETER_STRUCT()

};
    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
    }