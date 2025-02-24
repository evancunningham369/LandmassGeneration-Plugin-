#pragma once

class FMyComputeShaderWrapper
{
public:
	static FMyComputeShaderWrapper& Get()
	{
		static FMyComputeShaderWrapper Instance;
		return Instance;
	}

	void Dispatch(UWorld* World, uint32 NumVertices, const TArray<float>& DensityData);
private:
	FMyComputeShaderWrapper() = default;
	~FMyComputeShaderWrapper() = default;
	TArray<FVector3f> VerticesResults;

	FRDGBufferRef CreateEmptyBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements);
	FRDGTextureRef CreateTextureBuffer(FRDGBuilder& GraphBuilder, const void* Data, const uint32& SizeOfElement, const uint32& NumOfElements, const TCHAR* DebugName);
	void AddMarchingCubesShaderPass(UWorld* World, FRDGBuilder& GraphBuilder, const FRDGTextureUAVRef& DensityUAV, const uint32& NumVertices);
	void AddDensityCubesShaderPass(UWorld* World, FRDGBuilder& GraphBuilder, const TArray<float>& DensityData, FRDGTextureUAVRef& DensityUAV);
};