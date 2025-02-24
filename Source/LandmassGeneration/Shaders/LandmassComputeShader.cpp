#include "LandmassComputeShader.h"

IMPLEMENT_GLOBAL_SHADER(FDensityComputeShader, "/Project/LandmassComputeShader.usf", "FillDensity", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FMarchingCubesShader, "/Project/LandmassComputeShader.usf", "MarchingCube", SF_Compute);
