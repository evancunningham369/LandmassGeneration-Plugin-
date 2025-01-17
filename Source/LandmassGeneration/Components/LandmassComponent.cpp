// Fill out your copyright notice in the Description page of Project Settings.


#include "LandmassComponent.h"
#include "ProceduralMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "LandmassGeneration/Manager/LandmassManager.h"

#define DRAW_POINT(Location, Color) DrawDebugPoint(GetWorld(), Location, 20.f, Color, false, 1.f);
#define DRAW_POINT_PERM(Location, Color) DrawDebugPoint(GetWorld(), Location, 20.f, Color, true, -1.f);
#define DRAW_LINE(Start, End) DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.f);
#define DRAW_LINE_PERM(Start, End) DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1.f);

ULandmassComponent::ULandmassComponent()
{
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	ProceduralMesh->SetupAttachment(this);
}

void ULandmassComponent::BeginPlay()
{
	Super::BeginPlay();	
	UE_LOG(LogTemp, Warning, TEXT("LandmassType: %d"), LandmassType)
	UE_LOG(LogTemp, Warning, TEXT("LandmassOffset: %s"), *LandmassOffsetScaleDown.ToString())

	PopulateTerrainMap();
	CreateMeshData();
	PopulateVertexGrid();
	BuildMesh();
	//UE_LOG(LogTemp, Warning, TEXT("Mesh built"))
	//UE_LOG(LogTemp, Warning, TEXT("Grid Cell Size: %f"), GridCellSize);
}

void ULandmassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void ULandmassComponent::BuildMesh(bool bUpdateMesh)
{
	TArray<FVector>Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

	!bUpdateMesh ? 
	ProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true) :
	ProceduralMesh->UpdateMeshSection_LinearColor(0, Vertices, Normals, UVs, VertexColors, Tangents);
}

// Fix-me: Terrain[x][y][z] if sets a value outside of this range, overrides variables using the addresses right outside the array range
// Populates the vertices of the terrain map
void ULandmassComponent::PopulateTerrainMap()
{
	for (int32 x = 0; x < Width; x++)
	{
		for (int32 z = 0; z < Height; z++)
		{
			for (int32 y = 0; y < Width; y++)
			{
				if (x == 0 || x == Width - 1 || y == 0 || y == Width - 1 || z == Height - 1)
				{
					TerrainMap[x][y][z] = 1.0;
				}
				else
				{
					TerrainMap[x][y][z] = -1.0;
				}
			}
		}
	}
}
// populates the cubes of the terrain map, so number of cubes = number  of edges - 1
//		__ __
// EX: |__|__| - 3 edges, 2 cubes
//		
void ULandmassComponent::CreateMeshData()
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
					Cube[i] = TerrainMap[Corner.X][Corner.Y][Corner.Z];
				}

				MarchCube((FVector(x, y, z) * 100.f) + LandmassOffset, Cube);
			}
		}
	}
}

void ULandmassComponent::MarchCube(FVector position, TArray<float> Cube)
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
			Vertices.Add(VertexPosition);

			////Add number of triangles for this cube
			Triangles.Add(Vertices.Num() - 1);
			edgeIndex++;
		}
	}
}

int32 ULandmassComponent::GetScalarIndex(FVector LocalPosition)
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


// Calculate the configuration index by bitwise shifting by the index of the cube that is higher than the terrain.
// The integer value of that binary number is the index to use to search through the Triangulation Table
int32 ULandmassComponent::GetCubeConfiguration(TArray<float> Cube)
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

void ULandmassComponent::RemoveMesh(const FHitResult& HitResult, float Radius, const FVector& HitDirection)
{
	const FVector HitLocation = HitResult.Location;

	//DRAW_LINE(HitLocation, HitLocation + HitDirection * Radius);

	UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

	/*UE_LOG(LogTemp, Warning, TEXT("TopRight Location: %s"), *TopRight.ToString());
	UE_LOG(LogTemp, Warning, TEXT("BottomRight Location: %s"), *BottomRight.ToString());
	UE_LOG(LogTemp, Warning, TEXT("TopLeft Location: %s"), *TopLeft.ToString());
	UE_LOG(LogTemp, Warning, TEXT("BottomLeft Location: %s"), *BottomLeft.ToString());*/


	/*DRAW_POINT(TopRight, FColor::Black);
	DRAW_POINT(TopLeft, FColor::Blue);
	DRAW_POINT(BottomLeft, FColor::Yellow);
	DRAW_POINT(BottomRight, FColor::Purple);*/

	//UE_LOG(LogTemp, Warning, TEXT("Cell Size: %f"), GridCellSize)
	//DrawDebugBox(GetWorld(), HitLocation, FVector(GridCellSize / 2.f, GridCellSize / 2.f, 0.f), FColor::Green, true, -1.0f);

	//GetEffectedVectors(HitLocation, BoundingBox);
	ReCreateMesh(HitLocation, Radius);
	
	//BuildMesh(true);
}

void ULandmassComponent::ReCreateMesh(const FVector& HitLocation, float Radius)
{
	ClearMeshData();
	FVector SphereCenter(HitLocation);
	float SphereRadius = Radius;

	for (int32 x = 0; x < Width; x++)
	{
		for (int32 z = 0; z < Height; z++)
		{
			for (int32 y = 0; y < Width; y++)
			{	
				FVector Vertex = (FVector(x, y, z) * 100) + LandmassOffset;
				if (FVector::Dist(Vertex, SphereCenter) <= SphereRadius)
				{
					/*FVector RandomOffset = FVector(FMath::FRandRange(-1.f, 0.f), FMath::FRandRange(-1.f, 0.f), FMath::FRandRange(-1.f, 0.f));
					float PerlinNoise = FMath::PerlinNoise3D(Vertex + RandomOffset);
					UE_LOG(LogTemp, Warning, TEXT("Noise: %f"), PerlinNoise)*/
					TerrainMap[x][y][z] = 1.f;
				}
			}
		}
	}
	CreateMeshData();
	PopulateVertexGrid();
	BuildMesh();
}


void ULandmassComponent::InitializeLandmassOffsets(FVector Offset)
{
	LandmassOffset = Offset;
	LandmassOffsetScaleDown = FIntVector(FMath::RoundToInt(Offset.X / 100), FMath::RoundToInt(Offset.Y / 100), FMath::RoundToInt(Offset.Z / 100));
}

// Searches surrounding grid cells to collect all vertices within the explosion radius
void ULandmassComponent::GetEffectedVectors(const FVector& Point, const FBox& BoundingBox)
{
	FIntVector QueryPoint = GetGridCellIndex(Point);
	UE_LOG(LogTemp, Warning, TEXT("Query Point: %s"), *QueryPoint.ToString())

	// Check hitlocation grid cell and surrounding grid cells for effected vectors
	for(int32 x = -1; x < 2; x++)
	{
		for (int32 y = -1; y < 2; y++)
		{
			FIntVector GridCell = QueryPoint + FIntVector(x, y, 0);
			if (VertexGrid.Contains(GridCell))
			{
				for (FVector& Vertex : VertexGrid[GridCell])
				{
					if (BoundingBox.IsInsideXY(Vertex))
					{
						// Draw point over vertex inside bounding box
						DRAW_POINT(Vertex, FColor::Black);
						MoveVectorFromExplosion(Vertex);
					}
				}
			}
		}
	}
}

void ULandmassComponent::MoveVectorFromExplosion(FVector& Vertex)
{
	//To-Do
}

// Populates the Grid with cells and vertices within each cell
void ULandmassComponent::PopulateVertexGrid()
{
	for (const FVector& Vertex : Vertices)
	{
		FIntVector CellIndex = GetGridCellIndex(Vertex);

		if (!VertexGrid.FindOrAdd(CellIndex).Contains(Vertex))
		{
			VertexGrid.FindOrAdd(CellIndex).Add(Vertex);
		}
	}

	// print to visualize the grid and their respective vertices
	//PrintVertexGrid();

}

// Returns the grid cell index of the given vertex
FIntVector ULandmassComponent::GetGridCellIndex(const FVector& Vertex)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Vertex rounded: %d"), FMath::FloorToInt(Vertex.X))
	UE_LOG(LogTemp, Warning, TEXT("Vertex round with divide: %d"), FMath::FloorToInt(Vertex.X / GridCellSize))*/
	
	return FIntVector(
		FMath::FloorToInt(Vertex.X / GridCellSize),
		FMath::FloorToInt(Vertex.Y / GridCellSize),
		FMath::FloorToInt(Vertex.Z / GridCellSize)
	) * 1;
}

// Helper functions
void ULandmassComponent::PrintVertexGrid()
{
	for (const TPair<FIntVector, TArray<FVector>>& Pair : VertexGrid)
	{
		// Access the key
		const FIntVector& Key = Pair.Key;
		const TArray<FVector>& Values = Pair.Value;

		// Print the key
		UE_LOG(LogTemp, Log, TEXT("\nKey: %s\n"), *Key.ToString());
		// Print all values for that key
		for (const FVector& Value : Values)
		{
			UE_LOG(LogTemp, Log, TEXT("\tValue: %s\n"), *Value.ToString());
		}
	}
}

void ULandmassComponent::DrawVectors(const TArray<FVector>& Vectors)
{
	for (const FVector& Vector : Vectors)
	{
		DRAW_POINT_PERM(Vector, FColor::Red)
	}
}

//void ULandmassComponent::TestMarchCube(FVector position, int32 Index)
//{
//	if (Index == 0 || Index == 255)
//	{
//		return;
//	}
//	int32 edgeIndex = 0;
//	// for every triangle...(Never more than 5 triangles in any row of triangle table)
//	for (int32 i = 0; i < 5; i++)
//	{
//		// for every point in triangle...(Never more than 3 vertices in any given triangle)
//		for (int32 p = 0; p < 3; p++)
//		{	
//			// Get the vertex at that index
//			int32 indice = TriangleTable[Index][edgeIndex];
//			UE_LOG(LogTemp, Warning, TEXT("indice: %d"), indice)
//			if (indice == -1)
//			{
//				return;
//			}
//			// Get the vertices for that edge
//			FVector vert1 = position + EdgeTable[indice][0];
//			FVector vert2 = position + EdgeTable[indice][1];
//
//			// Position of vertex where mesh intersects edge
//			FVector vertPosition = (vert1 + vert2) / 2;
//
//			//Add position of vertex where mesh intersects
//			Vertices.Add(vertPosition);
//
//			//Add index of last added vertex
//			Triangles.Add(Vertices.Num() - 1);
//			edgeIndex++;
//		}
//		UE_LOG(LogTemp, Warning, TEXT("Vertices: %d"), Triangles.Num());
//	}
//}

void ULandmassComponent::ClearMeshData()
{
	Vertices.Empty();
	Triangles.Empty();
}

void ULandmassComponent::BuildTestCube()
{
	// Example: Create a simple quad
	TArray<FVector> TestVertices = {
		FVector(0.0f, 0.0f, 0.0f),
		FVector(0.0f, 100.0f, 0.0f),
		FVector(100.0f, 100.0f, 0.0f),
		FVector(100.0f, 0.0f, 0.0f),

		FVector(0.0f, 0.0f, 100.0f),
		FVector(0.0f, 100.0f, 100.0f),
		FVector(100.0f, 100.0f, 100.0f),
		FVector(100.0f, 0.0f, 100.0f)
	};

	TArray<int32> TestTriangles = {
		// top face
		0, 1, 2,
		0, 2, 3,
		// bottom face
		4, 5, 6,
		4, 6, 8,
		// left face
		1,5,4,
		1,4,0,
		// right face
		3,8,6,
		3,6,2,
		//front face
		0,4,8,
		0,8,3,
		//back face
		2,6,5,
		2,5,1
	};

	TArray<FVector>Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

	ProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
}

void ULandmassComponent::BuildTestTriangle()
{
	// Example: Create a simple triangle
	TArray<FVector> TestVertices = {
		FVector(0.0f, 0.0f, 0.0f),
		FVector(0.0f, 100.0f, 0.0f),
		FVector(0.0f, 0.0f, 100.0f)
	};
	TArray<int32> TestTriangles = {
		0, 2, 1
	};

	TArray<FVector>Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

	ProceduralMesh->CreateMeshSection_LinearColor(0, TestVertices, TestTriangles, Normals, UVs, VertexColors, Tangents, true);
}


