// Fill out your copyright notice in the Description page of Project Settings.

#include "LandmassManagerSubsystem.h"
#include "LandmassGeneration/Landmass/Landmass.h"
#include "LandmassGeneration/Components/LandmassComponent.h"
#include "LandmassGeneration/Compute/LandmassCompute.h"

void ULandmassManagerSubsystem::SpawnChunks()
{
	UE_LOG(LogTemp, Warning, TEXT("Attemping to spawn Chunks..."));
	UWorld* World = GetWorld();
	// How far apart each Landmass should spawn from another
	int32 TotalChunks = NumOfChunksX * NumOfChunksY * NumOfChunksZ;

	TArray<FVector> SpawnData;
	SpawnData.SetNum(TotalChunks);
	float OffsetAmount = ((Width - 1) * 100);
	ParallelFor(TotalChunks, [&](int32 Index)
		{
			int32 x = Index / (NumOfChunksY * NumOfChunksZ);
			int32 yz = Index % (NumOfChunksY * NumOfChunksZ);
			int32 y = yz / NumOfChunksZ;
			int32 z = yz % NumOfChunksZ;

			FVector Offset = FVector(x, y, 0) * OffsetAmount;
			SpawnData[Index] = Offset;

		}, EParallelForFlags::Unbalanced);

	static const int32 BATCH_SIZE = 10;
	Async(EAsyncExecution::ThreadPool, [this, World, SpawnData]
		{
			for (int32 i = 0; i < SpawnData.Num(); i += BATCH_SIZE)
			{
				AsyncTask(ENamedThreads::GameThread, [this, World, SpawnData, i]
					{
						int32 EndIndex = FMath::Min(i + BATCH_SIZE, SpawnData.Num());
						for (int32 j = i; j < EndIndex; j++)
						{
							UE_LOG(LogTemp, Warning, TEXT("Attemping to spawn chunk..."))

								ALandmass* Landmass = World->SpawnActor<ALandmass>(ALandmass::StaticClass(), SpawnData[j], FRotator::ZeroRotator);
							if (Landmass)
							{
								SpawnedLandmasses.Add(Landmass);
								Landmass->GetLandmassComponent()->CreateMesh(Width, Height);
							}
						}
					});
			}
		});
}

void ULandmassManagerSubsystem::SpawnChunk()
{
	UWorld* World = GetWorld();

	ALandmass* Landmass = World->SpawnActor<ALandmass>(ALandmass::StaticClass(), FVector(0, 0, 0), FRotator::ZeroRotator);
	if (Landmass->GetLandmassComponent())
	{
		Landmass->GetLandmassComponent()->CreateMesh(Width, Height);
	}
}

void ULandmassManagerSubsystem::CreateMap()
{
	UWorld* World = GetWorld();
	uint32 NumVertices = Width * Width * Height;
	DensityData.SetNum(NumVertices);
	PopulateDensityData();
	FMyComputeShaderWrapper::Get().Dispatch(World, NumVertices , DensityData);
}

void ULandmassManagerSubsystem::PopulateDensityData()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("Populate Terrain Map"))
		for (int32 x = 0; x < Width; x++)
		{
			for (int32 z = 0; z < Height; z++)
			{
				for (int32 y = 0; y < Width; y++)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Data: %s"), *FVector(x, y, z).ToString())
					if (z == Height - 1)
					{
						SetTerrainMapValue(x, y, z, 1.f);
					}
					else
					{
						SetTerrainMapValue(x, y, z, -1.f);
					}
				}
			}
		}
}

void ULandmassManagerSubsystem::SetTerrainMapValue(int32 X, int32 Y, int32 Z, float Value)
{
	int32 Index = X + (Z * Width) + (Y * Width * Height);
	DensityData[Index] = Value;
}