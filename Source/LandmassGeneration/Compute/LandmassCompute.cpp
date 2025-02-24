#include "LandmassCompute.h"
#include "CoreMinimal.h"
#include "LandmassGeneration/Shaders/LandmassComputeShader.h"
#include "LandmassGeneration/LandmassStructs.h"

#include "RenderGraphUtils.h"           // RDG utility functions
#include "RenderGraphResources.h"       // RDG buffer and texture handling
#include "RenderGraphBuilder.h"         // Required for FRDGBuilder
#include "ShaderParameterUtils.h"       // Required for shader parameters
#include "RHIResources.h"               // Handles RHI buffers and resources
#include <LandmassGeneration/Manager/LandmassManager.h>
#include "ComputeShaderReadback.h"

void FMyComputeShaderWrapper::Dispatch(UWorld* World, uint32 NumVertices, const TArray<float>& DensityData)
{
	ENQUEUE_RENDER_COMMAND(MyRenderCommand)(
		[World, this, NumVertices, DensityData](FRHICommandListImmediate& RHICmdList)
		{
			FRDGBuilder GraphBuilder(RHICmdList);
			FRDGTextureUAVRef DensityUAV;

			AddDensityCubesShaderPass(World, GraphBuilder, DensityData, DensityUAV);

			AddMarchingCubesShaderPass(World, GraphBuilder, DensityUAV, NumVertices);

		});
}

void FMyComputeShaderWrapper::AddMarchingCubesShaderPass(UWorld* World, FRDGBuilder& GraphBuilder, const FRDGTextureUAVRef& DensityUAV, const uint32& NumVertices)
{

	TShaderMapRef<FMarchingCubesShader> MarchingCubesShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	// Create GPU Buffer

	const uint32 Divisor = 3;
	uint32 NumTriangles = 2;
	FRDGBufferRef TrianglesOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(FTriangle), NumTriangles);
	FRDGBufferRef CounterOutputBuffer = CreateEmptyBuffer(GraphBuilder, sizeof(uint32), 1);
	
	// Create an UAV Buffer to enable RW on GPU Buffer
	FRDGBufferUAVRef TrianglesOutputBufferUAV = GraphBuilder.CreateUAV(TrianglesOutputBuffer);
	FRDGBufferUAVRef CounterOutputBufferUAV = GraphBuilder.CreateUAV(CounterOutputBuffer, PF_R32_UINT);

	AddClearUAVPass(GraphBuilder, CounterOutputBufferUAV, 0);
	// Allocate parameters
	FMarchingCubesShader::FParameters* MarchingCubesParams = GraphBuilder.AllocParameters<FMarchingCubesShader::FParameters>();
	MarchingCubesParams->Triangles = TrianglesOutputBufferUAV;
	MarchingCubesParams->DensityMap = DensityUAV;
	MarchingCubesParams->Counter = CounterOutputBufferUAV;
	FIntVector ConstMarchingCubesThreadGroups(
		1,
		1,
		1);

	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("Marching Cubes Shader Pass"),
		MarchingCubesShader,
		MarchingCubesParams,
		ConstMarchingCubesThreadGroups
	);

	FRHIGPUBufferReadback* TriangleReadbackBuffer = new FRHIGPUBufferReadback(TEXT("Triangle Compute Readback"));
	//FRHIGPUBufferReadback* CounterReadbackBuffer = new FRHIGPUBufferReadback(TEXT("Counter Compute Readback"));
	AddEnqueueCopyPass(GraphBuilder, TriangleReadbackBuffer, TrianglesOutputBuffer, sizeof(FTriangle) * NumTriangles); // Copy (n) bytes (uint32)
	//AddEnqueueCopyPass(GraphBuilder, CounterReadbackBuffer, CounterOutputBuffer, sizeof(uint32)); // Copy (n) bytes (uint32)
	
	GraphBuilder.Execute();

	FComputeShaderReadback::ProcessTriangleData(World, TriangleReadbackBuffer, sizeof(FTriangle), NumTriangles);
	//FComputeShaderReadback::ProcessCounterData(World, CounterReadbackBuffer, sizeof(uint32), 1);
}

void FMyComputeShaderWrapper::AddDensityCubesShaderPass(UWorld* World, FRDGBuilder& GraphBuilder, const TArray<float>& DensityData, FRDGTextureUAVRef& DensityUAV)
{
	TShaderMapRef<FDensityComputeShader> DensityShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	// Use RDG for GPU resource management
	// Create GPU Buffer

	FRDGTextureRef DensityBuffer = CreateTextureBuffer(
		GraphBuilder,
		DensityData.GetData(),
		sizeof(float),
		DensityData.Num(),
		TEXT("Density Data Buffer")
	);

	// Create an UAV Buffer to enable RW on GPU Buffer
	DensityUAV = GraphBuilder.CreateUAV(FRDGTextureUAVDesc(DensityBuffer));

	// Allocate parameters
	FDensityComputeShader::FParameters* DensityParams = GraphBuilder.AllocParameters<FDensityComputeShader::FParameters>();
	DensityParams->DensityMap = DensityUAV;

	// Dispatch the compute shader using FComputeShaderUtils
	// Number of Thread Groups
	const uint32 ThreadGroupSize = 8;
	/*FIntVector DensityThreadGroups(
		FMath::DivideAndRoundUp(NumVertices, ThreadGroupSize),
		FMath::DivideAndRoundUp(NumVertices, ThreadGroupSize),
		FMath::DivideAndRoundUp(NumVertices, ThreadGroupSize));*/

	FIntVector ConstDensityThreadGroups(
		1,
		1,
		1);

	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("Density Shader Pass"),
		DensityShader,
		DensityParams,
		ConstDensityThreadGroups
	);
}

// Create the buffer to hold data 
FRDGBufferRef FMyComputeShaderWrapper::CreateEmptyBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements)
{
	return GraphBuilder.CreateBuffer(
		FRDGBufferDesc::CreateStructuredDesc(SizeOfElement, NumOfElements),
		TEXT("OutputBuffer")
	);
}

FRDGTextureRef FMyComputeShaderWrapper::CreateTextureBuffer(FRDGBuilder& GraphBuilder, const void* Data, const uint32& SizeOfElement, const uint32& NumOfElements, const TCHAR* DebugName)
{
	FRDGTextureDesc Desc = FRDGTextureDesc::Create3D(
		FIntVector(2,2,2),
		PF_R32_FLOAT,
		FClearValueBinding::None,
		TexCreate_UAV | TexCreate_ShaderResource
	);
	
	FRDGTexture* Texture = GraphBuilder.CreateTexture(
		Desc,
		DebugName
	);
	


	return Texture;
}
