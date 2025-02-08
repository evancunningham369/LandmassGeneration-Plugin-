#pragma once

class FMyComputeShaderWrapper
{
public:
	static FMyComputeShaderWrapper& Get()
	{
		static FMyComputeShaderWrapper Instance;
		return Instance;
	}

	void Dispatch(uint32 SizeOfElement, uint32 NumElements);
	void CopyValueToGPU(uint32 ValueToCopy);
private:
	FMyComputeShaderWrapper() = default;
	~FMyComputeShaderWrapper() = default;

	bool bDataUploaded = false;
	void CheckReadbackBuffer(class FRHIGPUBufferReadback* ReadbackBuffer, const uint32& ElementSize, const uint32& TotalElements);
	FRDGBufferRef CreateOutputBuffer(FRDGBuilder& GraphBuilder, const uint32& SizeOfElement, const uint32& NumOfElements);
	FRDGBufferUAVRef CreateUAVBuffer(FRDGBuilder& GraphBuilder, const FRDGBufferRef& OutputBuffer);
	FRDGBufferSRVRef CreateTriangleTableSRV(FRDGBuilder& GraphBuilder);
	FRDGBufferRef UploadBuffer(FRDGBuilder& GraphBuilder, TArray<int32>& Table, const FString& Name);
	TArray<int32> GetFlatTriangleArray();
};