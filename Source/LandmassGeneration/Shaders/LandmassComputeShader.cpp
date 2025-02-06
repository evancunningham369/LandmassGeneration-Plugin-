#include "LandmassComputeShader.h"

IMPLEMENT_GLOBAL_SHADER(FMyComputeShader, "/Engine/Private/LandmassGeneration/LandmassComputeShader.usf", "MainCS", SF_Compute);
