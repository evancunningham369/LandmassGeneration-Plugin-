// Fill out your copyright notice in the Description page of Project Settings.


#include "LandmassComponent.h"
#include "LandmassGeneration/Manager/LandmassManager.h"
#include "LandmassGeneration/DebugMacros.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "DynamicMesh/MeshNormals.h"

using namespace UE::Geometry;

ULandmassComponent::ULandmassComponent()
{
	SetComponentTickEnabled(false);

	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetCollisionObjectType(ECC_GameTraceChannel1);
}

void ULandmassComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void ULandmassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULandmassComponent::CreateMesh(int32 TerrainWidth, int32 TerrainHeight)
{
	Width = TerrainWidth;
	Height = TerrainHeight;
	SetComplexAsSimpleCollisionEnabled(true);

	//UE_LOG(LogTemp, Warning, TEXT("LandmassType: %d"), LandmassType)
	//UE_LOG(LogTemp, Warning, TEXT("LandmassOffset: %s"), *LandmassOffsetScaleDown.ToString());
	TerrainMap.SetNum(Width * Width * Height);

	SetCastShadow(false);
	Async(EAsyncExecution::ThreadPool, [this]
		{
			PopulateTerrainMap();
			CreateMeshData();

			AsyncTask(ENamedThreads::GameThread, [this]()
				{
					BuildMesh();
				});
		});
}

// This is in a background thread
void ULandmassComponent::ReCreateMesh(const FVector& WorldHitLocation, float Radius)
{
	ResetMesh();

	float SquaredSphereRadius = Radius * Radius;

	AsyncTask(ENamedThreads::GameThread, [this, WorldHitLocation, Radius]()
		{
			DRAW_SPHERE_SIZE(WorldHitLocation, Radius, FColor::Green);
		});

	FColor RandomColor = FColor::MakeRandomColor();
	for (int32 x = 0; x < Width; x++)
	{
		for (int32 z = 0; z < Height; z++)
		{
			for (int32 y = 0; y < Width; y++)
			{
				FVector Vertex = (FVector(x, y, z) * 100) + LandmassOffset;
				//DRAW_POINT(Vertex, FColor::Blue);
				if (FVector::DistSquared(Vertex, WorldHitLocation) <= SquaredSphereRadius)
				{
					SetTerrainMapValue(x, y, z, 1.f);
				}
			}
		}
	}
	CreateMeshData();
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			BuildMesh();
		});
}

void ULandmassComponent::BuildMesh()
{
	Mesh.EnableVertexUVs(FVector2f::Zero());
	FMeshNormals::QuickComputeVertexNormals(Mesh);

	SetMesh(MoveTemp(Mesh));
	NotifyMeshUpdated();
}

// Use for a custom collision body.
void ULandmassComponent::UpdateBodyCollision()
{
	UE_LOG(LogTemp, Warning, TEXT("Setting Collision Body"));
	if (!CachedBodySetup)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Cached Body Setup"));
		return;
	}
	FBoxSphereBounds LocalBoxBounds = CalcBounds(FTransform::Identity);

	const FVector BoxCenter(LocalBoxBounds.Origin);
	const FVector BoxExtent(LocalBoxBounds.BoxExtent);

	CachedBodySetup->InvalidatePhysicsData();
	CachedBodySetup->AggGeom.BoxElems.Empty();

	FKBoxElem BoxElem;
	BoxElem.Center = BoxCenter;
	BoxElem.X = BoxExtent.X * 2.0f;
	BoxElem.Y = BoxExtent.Y * 2.0f;
	BoxElem.Z = BoxExtent.Z * 2.0f;
	
	CachedBodySetup->AggGeom.BoxElems.Add(BoxElem);
	CachedBodySetup->CreatePhysicsMeshes();
	RecreatePhysicsState();
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
				if (x == 0 || x == Width - 1 || y == 0 || y == Width - 1 || z == 0 || z == Height - 1)
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
					Cube[i] = GetTerrainMapValue(Corner.X, Corner.Y, Corner.Z);
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

			//Add position of vertex intersection point
			int32 VertexIndex = Mesh.AppendVertex(VertexPosition);
			TriangleIndices[p] = VertexIndex;

			//Add number of triangles for this cube
			//Triangles.Add(Vertices.Num() - 1);
			edgeIndex++;
		}
		// Causing problems with the collision being on the wrong side when hit
		Mesh.AppendTriangle(FIndex3i(TriangleIndices[0], TriangleIndices[1], TriangleIndices[2]));
	}
}

// Assigns each triangle a material based on it's world height. 
// Probably won't use this as I set the material for each chunk when I spawn them
void ULandmassComponent::AssignTriangleMaterials()
{
	for (int32 TriangleID : Mesh.TriangleIndicesItr())
	{
		FVector Center = Mesh.GetTriCentroid(TriangleID);
		int32 MaterialID = Center.Z > 2200 ? 1 : 0;
		Mesh.Attributes()->GetMaterialID()->SetValue(TriangleID, MaterialID);
	}
	if (GrassMaterial && SoilMaterial)
	{
		SetMaterial(1, GrassMaterial);
		SetMaterial(0, SoilMaterial);
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

void ULandmassComponent::ResetMesh()
{
	Mesh.Clear();
	Mesh.EnableVertexUVs(FVector2f::Zero());
}


int32 ULandmassComponent::GetTerrainMapIndex(int32 X, int32 Y, int32 Z) const
{
	return X + (Z * Width) + (Y * Width * Height);
}

void ULandmassComponent::GetTerrainMapCoordinates(int32 Index, int32& OutX, int32& OutY, int32& OutZ) const
{
	OutX = Index % Width;
	OutY = (Index / Width) % Height;
	OutZ = Index / (Width * Height);
}

void ULandmassComponent::SetTerrainMapValue(int32 X, int32 Y, int32 Z, float Value)
{
	int32 Index = GetTerrainMapIndex(X, Y, Z);
	TerrainMap[Index] = Value;
}

float ULandmassComponent::GetTerrainMapValue(int32 X, int32 Y, int32 Z) const
{
	int32 Index = GetTerrainMapIndex(X, Y, Z);
	return TerrainMap[Index];
}

void ULandmassComponent::DebugPrintTerrainMap()
{
	for (int32 X = 0; X < Width; X++)
	{
		for (int32  Z = 0; Z < Height; Z++)
		{
			for (int32 Y = 0; Y < Width; Y++)
			{
				float Value = GetTerrainMapValue(X, Y, Z);
				UE_LOG(LogTemp, Warning, TEXT("Value at (%d, %d, %d): %f"), X, Y, Z, Value);
			}
		}
	}
}

void ULandmassComponent::InitializeLandmassOffsets(FVector Offset)
{
	LandmassOffset = Offset;
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

void ULandmassComponent::DrawVectors()
{
	for (int32 VertexID : Mesh.VertexIndicesItr())
	{
		DRAW_POINT_PERM(Mesh.GetVertex(VertexID), FColor::Red)
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
	//TArray<FProcMeshTangent> Tangents;

	//ProceduralMesh->CreateMeshSection_LinearColor(0, TestVertices, TestTriangles, Normals, UVs, VertexColors, Tangents, true);
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
	//TArray<FProcMeshTangent> Tangents;

	//ProceduralMesh->CreateMeshSection_LinearColor(0, TestVertices, TestTriangles, Normals, UVs, VertexColors, Tangents, true);
}


