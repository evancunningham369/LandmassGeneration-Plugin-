// SimpleTriangleShader.h
#pragma once

#include "CoreMinimal.h"
#include "ShaderParameterStruct.h"
#include "GlobalShader.h"

// Vertex shader
class FVertexShaderExample : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FVertexShaderExample);
    SHADER_USE_PARAMETER_STRUCT(FVertexShaderExample, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER(FMatrix44f, ViewProjectionMatrix)
    END_SHADER_PARAMETER_STRUCT()

public:
    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return true;
    }
};

// Pixel shader
class FPixelShaderExample : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FPixelShaderExample);
    SHADER_USE_PARAMETER_STRUCT(FPixelShaderExample, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER(FVector4f, Color)
    END_SHADER_PARAMETER_STRUCT()

public:
    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return true;
    }
};