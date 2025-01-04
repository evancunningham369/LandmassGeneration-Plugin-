// Fill out your copyright notice in the Description page of Project Settings.


#include "LandmassComponent.h"
#include "ProceduralMeshComponent.h"
#include "DrawDebugHelpers.h"

#define DRAW_POINT(Location, Color) DrawDebugPoint(GetWorld(), Location, 20.f, Color, false, 5.f)
#define DRAW_LINE(Start, End) DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.f)

ULandmassComponent::ULandmassComponent()
{
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
}

void ULandmassComponent::BeginPlay()
{
	Super::BeginPlay();	
	UE_LOG(LogTemp, Warning, TEXT("Begin landmass"));
	PopulateTerrainMap();
	CreateMeshData();
	PopulateVertexGrid();
	BuildMesh();
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

void ULandmassComponent::PopulateTerrainMap()
{
	for (int32 x = 0; x < Width + 1; x++)
	{
		for (int32 z = 0; z < Height; z++)
		{
			for (int32 y = 0; y < Width + 1; y++)
			{
				float point = 0.f;

				PopulateNoNoise(x, y ,z, point);
				TerrainMap[x][y][z] = point;
			}
		}
	}
}

void ULandmassComponent::PopulateVertexGrid()
{
	for (const FVector& Vertex : Vertices)
	{
		FIntVector CellIndex = GetGridCellIndex(Vertex);

		VertexGrid.FindOrAdd(CellIndex).Add(Vertex);
	}
	//for (const TPair<FIntVector, TArray<FVector>>& Pair : VertexGrid)
	//{
	//	// Access the key
	//	const FIntVector& Key = Pair.Key;
	//	const TArray<FVector>& Values = Pair.Value;

	//	// Print the key
	//	UE_LOG(LogTemp, Log, TEXT("Key: %s\n"), *Key.ToString());
	//	for (const FVector& Value : Values)
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("\tValue: %s"), *Value.ToString());
	//	}
	//}

}

FIntVector ULandmassComponent::GetGridCellIndex(const FVector& Vertex)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Vertex rounded: %d"), FMath::FloorToInt(Vertex.X))
	UE_LOG(LogTemp, Warning, TEXT("Vertex round with divide: %d"), FMath::FloorToInt(Vertex.X / CellSize))*/

	return FIntVector(
		FMath::FloorToInt(Vertex.X / 100),
		FMath::FloorToInt(Vertex.Y / 100),
		FMath::FloorToInt(Vertex.Z / 100)
	) * -1;
}


void ULandmassComponent::PopulateWithPerlinNoise(int32 x, int32 y, int32 z, float& point)
{
	float thisHeight = FMath::PerlinNoise2D(
		FVector2D(
			x / divideBy * Scale + 0.001f,
			y / divideBy * Scale + 0.001f)
	);

	// If the z value of the terrain is below ground level...
	if (z <= thisHeight - TerrainSurface)
	{
		point = -1.f;
	}// If the z value of the terrain is above ground level...
	else if (z > thisHeight + TerrainSurface)
	{
		point = 1.f;
	}
	// else if the z value is not too high or below the ground...
	else
	{
		point = FMath::Abs(z - thisHeight);
	}
}

void ULandmassComponent::PopulateNoNoise(int32 x, int32 y, int32 z, float& point)
{
	point = (z <= TerrainHeight) ? -1.f : 1.f;
}

void ULandmassComponent::CreateMeshData()
{
	for (int32 x = 0; x < Width; x++)
	{
		for (int32 z = 0; z < Height - 1; z++)
		{
			for (int32 y = 0; y < Width; y++)
			{
				TArray<float> Cube;
				Cube.SetNum(8);
				// For every corner in the cube 
				for (int32 i = 0; i < 8; i++)
				{
					// Get the corner value relative to the current base position
					FIntVector Corner = FIntVector(x, y, z) + CornerTable[i];

					// Assigns a cube corner a "density" value from the terrain map(The variable point filled in by previous function)
					Cube[i] = TerrainMap[Corner.X][Corner.Y][Corner.Z];
					
				}

				MarchCube(FVector(x, y, z) * 100.f, Cube);
			}
		}
	}
}

void ULandmassComponent::RemoveMesh(const FVector& HitLocation, float Radius)
{

	UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

	FVector TopRight = HitLocation + FVector(-Radius, Radius, 0);
	FVector BottomRight = HitLocation + FVector(-Radius, -Radius, 0);
	FVector TopLeft = HitLocation + FVector(Radius, Radius, 0);
	FVector BottomLeft = HitLocation + FVector(Radius, -Radius, 0);

	UE_LOG(LogTemp, Warning, TEXT("TopRight Location: %s"), *TopRight.ToString());
	UE_LOG(LogTemp, Warning, TEXT("BottomRight Location: %s"), *BottomRight.ToString());
	UE_LOG(LogTemp, Warning, TEXT("TopLeft Location: %s"), *TopLeft.ToString());
	UE_LOG(LogTemp, Warning, TEXT("BottomLeft Location: %s"), *BottomLeft.ToString());


	DRAW_POINT(TopRight, FColor::Black);
	DRAW_POINT(TopLeft, FColor::Blue);
	DRAW_POINT(BottomLeft, FColor::Yellow);
	DRAW_POINT(BottomRight, FColor::Purple);


	FBox BoundingBox = FBox(BottomRight, TopLeft);

	DrawDebugBox(GetWorld(), BoundingBox.GetCenter(), BoundingBox.GetExtent(), FColor::Green, false, 5.0f);

	GetEffectedVectors(HitLocation, BoundingBox);

	//FVector ClosestPoint = GetClosestPoint(TopLeft, BoundingBox);

	/*UE_LOG(LogTemp, Warning, TEXT("Out of loop..."));

	CreateMeshData();
	BuildMesh(true);*/
}

FVector ULandmassComponent::GetClosestPoint(const FVector& point, const FBox& BoundingBox)
{
	FVector ClosestVertex;
	float MinDistanceSquared = TNumericLimits<float>::Max();

	for (const FVector& Vertex : Vertices)
	{
		float DistanceSquared = FVector::DistSquared(point, Vertex);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), IsInsideBoundingBox(point, BoundingBox) ? TEXT("True") : TEXT("False"))
		if (BoundingBox.IsInsideXY(Vertex) && DistanceSquared < MinDistanceSquared)
		{
			MinDistanceSquared = DistanceSquared;

			ClosestVertex = Vertex;
		}
	}
	return ClosestVertex;
}

void ULandmassComponent::GetEffectedVectors(const FVector& Point, const FBox& BoundingBox)
{
	FIntVector QueryPoint = GetGridCellIndex(Point);

	DRAW_POINT(FVector(QueryPoint), FColor::Black);
	if (!VertexGrid.Contains(QueryPoint))
	{
		UE_LOG(LogTemp, Warning, TEXT("QueryPoint %s not found in VertexGrid!"), *QueryPoint.ToString());
		return;
	}

	for (const FVector& Vertex : VertexGrid[QueryPoint])
	{
		DRAW_POINT(Vertex + FVector(.5, 0 ,0), FColor::Yellow);
		if (BoundingBox.IsInsideXY(Vertex))
		{
			DRAW_POINT(Vertex, FColor::Black);
		}
	}

	/*for (const FVector& Vertex : Vertices)
	{
		DRAW_POINT(Vertex, FColor::Yellow);
		if (BoundingBox.IsInsideXY(Vertex))
		{
			DRAW_POINT(Vertex, FColor::Black);
		}
	}*/
}

void ULandmassComponent::MarchCube(FVector position, TArray<float> Cube)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *position.ToString());
	// Converts Cube verticies into binary
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
			// Get a vertex at that index
			int32 indice = TriangleTable[Index][edgeIndex];
			if (indice == -1)
			{
				return;
			}

			// Get the vertices of an edge for that vertex
			FVector vert1 = position + EdgeTable[indice][0];
			FVector vert2 = position + EdgeTable[indice][1];

			// Estimate the position of the vertex of intersection point
			FVector vertPosition = (vert1 + vert2) / 2;

			//Add position of vertex intersection point
			Vertices.Add(vertPosition);

			//Add number of triangles for this cube
			Triangles.Add(Vertices.Num() - 1);
			edgeIndex++;
		}
	}
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

void ULandmassComponent::CreateConfiguration()
{
	/*ConfigIndex++;
	UE_LOG(LogTemp, Warning, TEXT("Creating configuation %d"), ConfigIndex);
	ClearMeshData();
	MarchCube(FVector(0,0,5), ConfigIndex);
	BuildMesh();*/
}

void ULandmassComponent::TestMarchCube(FVector position, int32 Index)
{
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
			// Get the vertex at that index
			int32 indice = TriangleTable[Index][edgeIndex];
			UE_LOG(LogTemp, Warning, TEXT("indice: %d"), indice)
			if (indice == -1)
			{
				return;
			}
			// Get the vertices for that edge
			FVector vert1 = position + EdgeTable[indice][0];
			FVector vert2 = position + EdgeTable[indice][1];

			// Position of vertex where mesh intersects edge
			FVector vertPosition = (vert1 + vert2) / 2;

			//Add position of vertex where mesh intersects
			Vertices.Add(vertPosition);

			//Add index of last added vertex
			Triangles.Add(Vertices.Num() - 1);
			edgeIndex++;
		}
		UE_LOG(LogTemp, Warning, TEXT("Vertices: %d"), Triangles.Num());
	}
}

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


