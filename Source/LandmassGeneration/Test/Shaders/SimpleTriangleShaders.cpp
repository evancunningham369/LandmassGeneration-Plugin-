#include "SimpleTriangleShaders.h"

IMPLEMENT_GLOBAL_SHADER(FVertexShaderExample, "/Project/SimpleTriangleShaders.usf", "MainVS", SF_Vertex)
IMPLEMENT_GLOBAL_SHADER(FPixelShaderExample, "/Project/SimpleTriangleShaders.usf", "MainPS", SF_Pixel)