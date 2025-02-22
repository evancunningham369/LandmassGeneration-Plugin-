#pragma once
#include "CoreMinimal.h"
#include "LandmassGeneration/DebugMacros.h"

class FComputeShaderReadback
{
public:
	static void ProcessVertexData(UWorld* World,
		FRHIGPUBufferReadback* ReadbackBuffer,
		const uint32& ElementSize,
		const uint32& TotalElements)
	{
		CheckReadbackBuffer<FVector4f>(World, ReadbackBuffer, ElementSize, TotalElements,
			[World](FVector4f* Data, uint32 TotalElements)
			{
				for (uint32 x = 0; x < TotalElements; x++)
				{
					FColor DensityValueColor = Data[x].W == 1.f ? FColor::Blue : FColor::Red;
					FVector ScaledVertex = (FVector)Data[x] * 100;
					DRAW_POINT_PERM_STATIC(World, ScaledVertex, DensityValueColor);
					UE_LOG(LogTemp, Warning, TEXT("Vertex: %s"), *Data[x].ToString());
				}
				UE_LOG(LogTemp, Warning, TEXT("Total Vertices: %d"), TotalElements);
			});
	}

private:

	template<typename T>
	static void CheckReadbackBuffer(UWorld* World,
		FRHIGPUBufferReadback* ReadbackBuffer,
		const uint32& ElementSize,
		const uint32& TotalElements,
		TFunction<void(T*, uint32)> ProcessDataCallback)
	{
		uint32 TotalBufferSize = ElementSize * TotalElements;

		AsyncTask(ENamedThreads::ActualRenderingThread,
			[World, ReadbackBuffer, TotalElements, ElementSize, TotalBufferSize, ProcessDataCallback]()
			{
				if (ReadbackBuffer->IsReady())
				{
					T* Data = (T*)ReadbackBuffer->Lock(TotalBufferSize);

					AsyncTask(ENamedThreads::GameThread,
						[World, Data, TotalElements, ProcessDataCallback]()
						{
							ProcessDataCallback(Data, TotalElements);
						});
					
					ReadbackBuffer->Unlock();
					delete ReadbackBuffer;
				}
				else
				{
					AsyncTask(ENamedThreads::GameThread,
						[World, ReadbackBuffer, ElementSize, TotalElements, ProcessDataCallback]()
					{
						UE_LOG(LogTemp, Warning, TEXT("Buffer readback not ready...retrying..."));
						FTimerHandle TimerHandle;
						World->GetTimerManager().SetTimer(
							TimerHandle,
							[World, ReadbackBuffer, ElementSize, TotalElements, ProcessDataCallback]()
							{
								CheckReadbackBuffer<T>(World, ReadbackBuffer, ElementSize, TotalElements, ProcessDataCallback);
							},
							0.05f,
							false
						);
					});
				}
			});
	}

	
};