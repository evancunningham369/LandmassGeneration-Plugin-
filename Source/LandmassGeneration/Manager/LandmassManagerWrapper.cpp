// Fill out your copyright notice in the Description page of Project Settings.


#include "LandmassManagerWrapper.h"
#include "LandmassManager.h"

ALandmassManagerWrapper::ALandmassManagerWrapper()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ALandmassManagerWrapper::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALandmassManagerWrapper::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UWorld* World = GetWorld();
	if (World)
	{
		ULandmassManager::Get()->SpawnChunks(World, SpawnOffset, NumOfChunksX, NumOfChunksY);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("World is invalid"))
	}
}

void ALandmassManagerWrapper::CreateMeshData()
{
	TArray<FIntVector> CornerTable = ULandmassManager::Get()->GetCornerTable();

	for (int32 x = 0; x < Width - 1; x++)
	{
		for (int32 z = 0; z < Height - 1; z++)
		{
			for (int32 y = 0; y < Width - 1; y++)
			{
				TArray<float> Cube;
				Cube.SetNum(8);
				// For the first vertex
				for (int32 i = 0; i < 8; i++)
				{
					// Get the corner value relative to the current vertex position
					FIntVector Corner = FIntVector(x, y, z) + CornerTable[i];

					// Assigns a cube corner a "density" value from the terrain map(The variable point filled in by previous function)
					Cube[i] = GetTerrainMapValue(Corner.X, Corner.Y, Corner.Z);
				}

				MarchCube(FVector(x, y, z) * 100.f, Cube);
			}
		}
	}
	DynamicMesh->SetMesh(MoveTemp(Mesh));
}

void ALandmassManagerWrapper::MarchCube(FVector position, TArray<float> Cube)
{
	TArray<TArray<int32>> TriangleTable = ULandmassManager::Get()->GetTriangulationTable();
	TArray<TArray<FVector>> EdgeTable = ULandmassManager::Get()->GetEdgeTable();
	// Converts Cube verticies into binary. Vertices inside the mesh = 1, outside = 0
	int32 Index = GetCubeConfiguration(Cube);

	// Triangulation Table is only valid with indicies between (0,255)
	if (Index == 0 || Index == 255)
	{
		return;
	}
	
	int32 edgeIndex = 0;

	// for every triangle...(Never more than 5 triangles in any row of triangle table)
	for (int32 i = 0; i < 5; i++)
	{
		FIndex3i TriangleIndices;

		// for every point in triangle...(Never more than 3 vertices in any given triangle)
		for (int32 p = 0; p < 3; p++)
		{
			// Get an edge in the table
			int32 indice = TriangleTable[Index][edgeIndex];
			if (indice == -1)
			{
				return;
			}

			// Get the first vertex of the edge that is intersected
			FVector EdgeOffset1 = EdgeTable[indice][0];
			FVector vert1 = position + EdgeOffset1;
			float value1 = Cube[GetScalarIndex(EdgeOffset1)];

			// Get the second vertex of the edge that is intersected
			FVector EdgeOffset2 = EdgeTable[indice][1];
			FVector vert2 = position + EdgeOffset2;
			float value2 = Cube[GetScalarIndex(EdgeOffset2)];

			float t = (TerrainSurface - value1) / (value2 - value1);
			FVector VertexPosition = vert1 + t * (vert2 - vert1);

			// Estimate the position of the vertex of intersection point
			//FVector vertPosition = (vert1 + vert2) / 2;

			//Add position of vertex intersection point
			int VertexIndex = Mesh.AppendVertex(VertexPosition);
			//Add number of triangles for this cube
			TriangleIndices[p] = VertexIndex;
			edgeIndex++;
		}

		Mesh.AppendTriangle(FIndex3i(TriangleIndices[0], TriangleIndices[1], TriangleIndices[2]));
	}
}

int32 ALandmassManagerWrapper::GetCubeConfiguration(TArray<float> Cube)
{
	int32 configurationIndex = 0;
	for (int32 i = 0; i < 8; i++)
	{
		if (Cube[i] > TerrainSurface)
		{
			configurationIndex |= 1 << i;
		}
	}
	return configurationIndex;
}

int32 ALandmassManagerWrapper::GetScalarIndex(FVector LocalPosition)
{
	// Map local cube vertex positions to indices in the Cube array
	if (LocalPosition == FVector(0.0f, 0.0f, 0.0f)) return 0;
	if (LocalPosition == FVector(100.0f, 0.0f, 0.0f)) return 1;
	if (LocalPosition == FVector(100.0f, 0.0f, 100.0f)) return 2;
	if (LocalPosition == FVector(0.0f, 0.0f, 100.0f)) return 3;
	if (LocalPosition == FVector(0.0f, 100.0f, 0.0f)) return 4;
	if (LocalPosition == FVector(100.0f, 100.0f, 0.0f)) return 5;
	if (LocalPosition == FVector(100.0f, 100.0f, 100.0f)) return 6;
	if (LocalPosition == FVector(0.0f, 100.0f, 100.0f)) return 7;

	return -1; // Invalid position
}

int32 ALandmassManagerWrapper::GetTerrainMapIndex(int32 X, int32 Y, int32 Z) const
{
	return X + (Z * Width) + (Y * Width * Height);
}

void ALandmassManagerWrapper::GetTerrainMapCoordinates(int32 Index, int32& OutX, int32& OutY, int32& OutZ) const
{
	OutX = Index % Width;
	OutY = (Index / Width) % Height;
	OutZ = Index / (Width * Height);
}

void ALandmassManagerWrapper::SetTerrainMapValue(int32 X, int32 Y, int32 Z, float Value)
{
	int32 Index = GetTerrainMapIndex(X, Y, Z);
	TerrainMap[Index] = Value;
}

float ALandmassManagerWrapper::GetTerrainMapValue(int32 X, int32 Y, int32 Z) const
{
	int32 Index = GetTerrainMapIndex(X, Y, Z);
	return TerrainMap[Index];
}

void ALandmassManagerWrapper::DebugPrintTerrainMap()
{
	for (int32 X = 0; X < Width; X++)
	{
		for (int32 Z = 0; Z < Height; Z++)
		{
			for (int32 Y = 0; Y < Width; Y++)
			{
				float Value = GetTerrainMapValue(X, Y, Z);
				UE_LOG(LogTemp, Warning, TEXT("Value at (%d, %d, %d): %f"), X, Y, Z, Value);
			}
		}
	}
}


