#include "LandmassComputeShader.h"

IMPLEMENT_GLOBAL_SHADER(FDensityComputeShader, "/Project/LandmassComputeShader.usf", "CreateMesh", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FEditDensityComputeShader, "/Project/LandmassComputeShader.usf", "CreateCrater", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FMarchingCubesShader, "/Project/LandmassComputeShader.usf", "MarchingCube", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FTestShader, "/Project/LandmassComputeShader.usf", "TestShader", SF_Compute);
