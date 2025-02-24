#pragma once
#include "CoreMinimal.h"
#include "LandmassGeneration/DebugMacros.h"
#include "LandmassGeneration/LandmassStructs.h"


class FComputeShaderReadback
{
public:
	static void ProcessVertexData(UWorld* World,
		FRHIGPUBufferReadback* ReadbackBuffer,
		const uint32& ElementSize,
		const uint32& TotalElements)
	{
		if (!ReadbackBuffer)
		{
			UE_LOG(LogTemp, Warning, TEXT("ReadbackBuffer is null!"));
			return;
		}
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

	static void ProcessTriangleData(UWorld* World,
		FRHIGPUBufferReadback* ReadbackBuffer,
		const uint32& ElementSize,
		const uint32& TotalElements)
	{
		if (!ReadbackBuffer)
		{
			UE_LOG(LogTemp, Warning, TEXT("ReadbackBuffer is null!"));
			return;
		}
		CheckReadbackBuffer<FTriangle>(World, ReadbackBuffer, ElementSize, TotalElements,
			[World](FTriangle* Data, uint32 TotalElements)
			{
				for (uint32 x = 0; x < TotalElements; x++)
				{
					const FTriangle& Triangle = Data[x];

					FVector Vertex1(Triangle.Vertex1 * 100);
					FVector Vertex2(Triangle.Vertex2 * 100);
					FVector Vertex3(Triangle.Vertex3 * 100);

					/*DRAW_LINE_PERM_STATIC(World, Vertex1, Vertex2);
					DRAW_LINE_PERM_STATIC(World, Vertex2, Vertex3);
					DRAW_LINE_PERM_STATIC(World, Vertex3, Vertex1);*/

					DRAW_POINT_PERM_STATIC(World, Vertex1, FColor::Blue);
					DRAW_POINT_PERM_STATIC(World, Vertex2, FColor::Green);
					DRAW_POINT_PERM_STATIC(World, Vertex3, FColor::Red);
					
					PRINT_VECTOR_NAME(FString("Vertex1"), Vertex1);
					PRINT_VECTOR_NAME(FString("Vertex2"), Vertex2);
					PRINT_VECTOR_NAME(FString("Vertex3"), Vertex3);
				}
				UE_LOG(LogTemp, Warning, TEXT("Total Triangles: %d"), TotalElements);
			});
	}

	static void ProcessCounterData(UWorld* World,
		FRHIGPUBufferReadback* ReadbackBuffer,
		const uint32& ElementSize,
		const uint32& TotalElements)
	{
		if (!ReadbackBuffer)
		{
			UE_LOG(LogTemp, Warning, TEXT("ReadbackBuffer is null!"));
			return;
		}
		CheckReadbackBuffer<uint32>(World, ReadbackBuffer, ElementSize, TotalElements,
			[World](uint32* Data, uint32 TotalElements)
			{
				UE_LOG(LogTemp, Warning, TEXT("Counter: %d"), Data[0]);
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