// Fill out your copyright notice in the Description page of Project Settings.


#include "LandmassComponent.h"
#include "LandmassGeneration/Manager/LandmassManager.h"
#include "LandmassGeneration/DebugMacros.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "DynamicMesh/MeshNormals.h"
#include "Trace/Trace.h"

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
	SetComplexAsSimpleCollisionEnabled(true);

}

void ULandmassComponent::BuildMesh()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{
			TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("Compute Normals"));
			FMeshNormals::QuickComputeVertexNormals(Mesh);

			AsyncTask(ENamedThreads::GameThread, [this]()
				{
					TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("Set Mesh"));
					
					SetMesh(MoveTemp(Mesh));
					UE_LOG(LogTemp, Warning, TEXT("Vertex Total: %d"), Mesh.VertexCount())

				});
		});
}

void ULandmassComponent::CreateMesh(int32 TerrainMeshWidth, int32 TerrainMeshHeight)
{
	UE_LOG(LogTemp, Warning, TEXT("Landmass Spawned"));

	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("CreateMesh"))
	Width = TerrainMeshWidth;
	Height = TerrainMeshHeight;

	//UE_LOG(LogTemp, Warning, TEXT("LandmassType: %d"), LandmassType)
	//UE_LOG(LogTemp, Warning, TEXT("LandmassOffset: %s"), *LandmassOffsetScaleDown.ToString());
	TerrainMap.SetNum(Width * Width * Height);

	SetCastShadow(false);

	Async(EAsyncExecution::ThreadPool, [this]
		{
			PopulateTerrainMap();
			CreateMeshDataOptimized();

			AsyncTask(ENamedThreads::GameThread, [this]()
				{
					//UE_LOG(LogTemp, Warning, TEXT("Vertex Count: %d"), Mesh.VertexCount())
					BuildMesh();
				});
		});
}

void ULandmassComponent::PopulateTerrainMap()
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
	UE_LOG(LogTemp, Warning, TEXT("Terrain Map Total: %d"), TerrainMap.Num())

}

void ULandmassComponent::CreateMeshDataOptimized()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("Create Mesh Data Optimized"));

	const TArray<FIntVector> CornerTable = ULandmassManager::Get()->GetCornerTable();
	const  TArray<TArray<int32>>& TriangleTable = ULandmassManager::Get()->GetTriangulationTable();
	const TArray<TArray<FVector>>& EdgeTable = ULandmassManager::Get()->GetEdgeTable();

	TArray<FDynamicMesh3> ThreadMeshes;
	ThreadMeshes.SetNum(Width - 1);
	

	ParallelFor(Width - 1, [&](int32 x)
		{
			float Cube[8];
			FIndex3i TriangleIndices;
			FDynamicMesh3& CurrentMesh = ThreadMeshes[x];
			
			for (int32 z = 0; z < Height - 1; z++)
			{
				for (int32 y = 0; y < Width - 1; y++)
				{
					const FVector BasePosition = (FVector(x, y, z) * 100.f);

					for (int32 i = 0; i < 8; i++)
					{
						FIntVector Corner = CornerTable[i];
						Cube[i] = GetTerrainMapValue(x + Corner.X, y + Corner.Y, z + Corner.Z);
					}

					MarchCubeOptimized(BasePosition, Cube, TriangleTable, EdgeTable, CurrentMesh, TriangleIndices);
				}
			}
		});

	Mesh.Clear();

	for (const FDynamicMesh3& ThreadMesh : ThreadMeshes)
	{
		int32 BaseVertexIndex = Mesh.VertexCount();

		for (int32 VertexID : ThreadMesh.VertexIndicesItr())
		{
			Mesh.AppendVertex(ThreadMesh.GetVertex(VertexID));
		}

		for (int32 TriangleID : ThreadMesh.TriangleIndicesItr())
		{
			FIndex3i Triangle = ThreadMesh.GetTriangle(TriangleID);
			Triangle.A += BaseVertexIndex;
			Triangle.B += BaseVertexIndex;
			Triangle.C += BaseVertexIndex;
			Mesh.AppendTriangle(Triangle);
		}
	}
}

void ULandmassComponent::MarchCubeOptimized(
	const FVector& position, 
	const float Cube[], 
	const TArray<TArray<int32>>& TriangleTable, 
	const TArray<TArray<FVector>>& EdgeTable, 
	FDynamicMesh3& CurrentMesh, 
	FIndex3i& TriangleIndices
)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("March Cube Optimized"));

	int32 Index = GetCubeConfigurationOptimized(Cube);

	// Triangulation Table is only valid with indicies between (0,255)
	if (Index == 0 || Index == 255) return;
	
	// Get row of edges
	const TArray<int32>& CurrentTriangleTable = TriangleTable[Index];
	int32 edgeIndex = 0;
	FIndex3i TriangleIndicesArr;

	FVector vert1, vert2;
	float value1, value2, t;

	// for every triangle...(Never more than 5 triangles in any row of triangle table)
	while(edgeIndex < CurrentTriangleTable.Num() && CurrentTriangleTable[edgeIndex] != -1)
	{
		// for every point in triangle...(Never more than 3 vertices in any given triangle)
		for (int32 p = 0; p < 3; p++)
		{
			// Get an edge value[0 - 11] in the table row
			const int32 indice = CurrentTriangleTable[edgeIndex];

			// Get Array of 2 base vectors that make up the vertices of that edge value
			const TArray<FVector>& CurrentEdge = EdgeTable[indice];

			// Get the 2 base vectors that make up that edge
			const FVector& EdgeOffset1 = CurrentEdge[0];
			const FVector& EdgeOffset2 = CurrentEdge[1];

			// Get the actual world position of the vertices that make up that edge
			vert1 = position + EdgeOffset1;
			vert2 = position + EdgeOffset2;

			value1 = Cube[GetScalarIndex(EdgeOffset1)];
			value2 = Cube[GetScalarIndex(EdgeOffset2)];

			t = (TerrainSurface - value1) / (value2 - value1);
			FVector VertexPosition = vert1 + t * (vert2 - vert1);
			//UE_LOG(LogTemp, Warning, TEXT("Vertex Position: %s"), *VertexPosition.ToString());

			//Add position of vertex intersection point
			int32 VertexIndex = CurrentMesh.AppendVertex(VertexPosition);
			TriangleIndices[p] = VertexIndex;

			//Add number of triangles for this cube
			//Triangles.Add(Vertices.Num() - 1);
			edgeIndex++;
		}
		CurrentMesh.AppendTriangle(TriangleIndices);
	}
}

void ULandmassComponent::ReCreateMeshLegacy(const FVector& WorldHitLocation, float Radius)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("ReCreate Mesh Legacy"));

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
				FVector Vertex = (FVector(x, y, z) * 100) + GetComponentLocation();
				/*AsyncTask(ENamedThreads::GameThread, [this, Vertex]()
					{
						DRAW_POINT(Vertex, FColor::Green);
					});*/
				if (FVector::DistSquared(Vertex, WorldHitLocation) <= SquaredSphereRadius)
				{
					SetTerrainMapValue(x, y, z, 1.f);
				}
			}
		}
	}
	CreateMeshDataOptimized();
	UpdateMesh();
}

void ULandmassComponent::UpdateMesh()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("Compute Normals"));
	FMeshNormals::QuickComputeVertexNormals(Mesh);

	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			//TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("Edit Mesh Operation"));
			TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("Direct Update"));

			FDynamicMesh3* InternalMesh = GetMesh();
			if (InternalMesh)
			{
				*InternalMesh = MoveTemp(Mesh);
				MarkRenderStateDirty();

				Async(EAsyncExecution::ThreadPool, [this]()
					{
						if (UBodySetup* BodySetup = GetBodySetup())
						{
							BodySetup->InvalidatePhysicsData();
							BodySetup->CreatePhysicsMeshes();

						}

						AsyncTask(ENamedThreads::GameThread, [this]()
							{
								RecreatePhysicsState();
							});
					});
			}
		});
}


void ULandmassComponent::UpdateMeshCollision()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetCollisionObjectType(ECC_GameTraceChannel1);
	SetComplexAsSimpleCollisionEnabled(true);
}

void ULandmassComponent::ReCreateMesh(const FVector& WorldHitLocation, float Radius)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("Recreating Mesh"))

		ResetMesh();
	TArray<FVector> VerticesToRemove;

	float SquaredSphereRadius = Radius * Radius;

	DRAW_SPHERE_SIZE(WorldHitLocation, Radius, FColor::Green);

	FColor RandomColor = FColor::MakeRandomColor();
	EditMesh([&](FDynamicMesh3& Mesh)
		{
			for (int32 VertexId : Mesh.VertexIndicesItr())
			{
				FVector Vertex = Mesh.GetVertex(VertexId);
				if (double Distance = FVector::DistSquared(Vertex, WorldHitLocation) <= SquaredSphereRadius)
				{
					Vertex.Z -= FMath::Abs(Distance - Radius);
					Mesh.SetVertex(VertexId, Vertex);
				}
			}
			FMeshNormals::QuickComputeVertexNormals(Mesh);
		}, EDynamicMeshComponentRenderUpdateMode::FastUpdate);
}

void ULandmassComponent::CreateGround()
{
	for (int32 x = 0; x < NumSquares; x++)
	{
		for (int32 y = 0; y < NumSquares; y++)
		{
			CreateSquare((x * TerrainWidth), (y * TerrainWidth));
		}
	}
}

void ULandmassComponent::CreateSquare(float XOffset, float YOffset)
{
	FVector Vertex1(XOffset + TerrainWidth, YOffset, 0.f);
	FVector Vertex2(XOffset, YOffset + TerrainWidth, 0.f);
	FVector Vertex3(XOffset, YOffset, 0.f);

	int32 VertexId1 = Mesh.AppendVertex(Vertex1);
	int32 VertexId3 = Mesh.AppendVertex(Vertex2);
	int32 VertexId2 = Mesh.AppendVertex(Vertex3);

	Mesh.AppendTriangle(FIndex3i(VertexId1, VertexId2, VertexId3));

	FVector Vertex4(XOffset + TerrainWidth, YOffset + TerrainWidth, 0.f);

	int32 VertexId4 = Mesh.AppendVertex(Vertex4);

	Mesh.AppendTriangle(FIndex3i(VertexId4, VertexId1, VertexId3));
}

void ULandmassComponent::CreateCraterAtLocation(FVector HitLocation, float CraterDepth)
{
	TArray<int32> SquareVertices;
	TArray<int32> TrianglesToRemove;

	for (int32 TriangleId : Mesh.TriangleIndicesItr())
	{
		FVector Center = Mesh.GetTriCentroid(TriangleId);
		if (FVector::DistSquared(Center, HitLocation) <= 500.f)
		{
			TrianglesToRemove.Add(TriangleId);

			FVector V1 = Mesh.GetTriVertex(TriangleId, 0);
			FVector V2 = Mesh.GetTriVertex(TriangleId, 1);
			FVector V3 = Mesh.GetTriVertex(TriangleId, 2);
			DRAW_POINT(V1, FColor::Red);
			DRAW_POINT(V2, FColor::Red);
			DRAW_POINT(V3, FColor::Red);

		}
	}
}

void ULandmassComponent::CreateTriangle(float XOffset, float YOffset)
{
	FVector Vertex1(XOffset, 0, 0);
	DRAW_POINT_PERM(Vertex1, FColor::Blue);
	FVector Vertex2(XOffset + 100, 0, 0);
	DRAW_POINT_PERM(Vertex2, FColor::Green);
	FVector Vertex3((Vertex1.X + Vertex2.X) / 2, 0, -100);
	DRAW_POINT_PERM(Vertex3, FColor::Red);

	int32 VertexId1 = Mesh.AppendVertex(Vertex1);
	int32 VertexId2 = Mesh.AppendVertex(Vertex2);
	int32 VertexId3 = Mesh.AppendVertex(Vertex3);

	Mesh.AppendTriangle(FIndex3i(VertexId1, VertexId2, VertexId3));
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

int32 ULandmassComponent::GetCubeConfigurationOptimized(const float Cube[])
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
		DRAW_POINT_PERM(Mesh.GetVertex(VertexID), FColor::Blue)
	}
}

void ULandmassComponent::PrintVectors()
{
	for (int32 VertexID : Mesh.VertexIndicesItr())
	{
		UE_LOG(LogTemp, Warning, TEXT("Vertex: %s"), *Mesh.GetVertex(VertexID).ToString())
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

void ULandmassComponent::CreateTestCrater()
{
	FVector Vertex1(0, 0, 0);
	FVector Vertex2(100, 0, 0);
	FVector Vertex3(0, 100, 0);
	FVector Vertex4(100, 100, 0);

	FVector Vertex5(50, 50, -100);

	int32 VertexId1 = Mesh.AppendVertex(Vertex1);
	int32 VertexId2 = Mesh.AppendVertex(Vertex2);
	int32 VertexId3 = Mesh.AppendVertex(Vertex3);
	int32 VertexId4 = Mesh.AppendVertex(Vertex4);

	int32 VertexId5 = Mesh.AppendVertex(Vertex5);

	Mesh.AppendTriangle(FIndex3i(VertexId2, VertexId1, VertexId5));
	Mesh.AppendTriangle(FIndex3i(VertexId1, VertexId3, VertexId5));
	Mesh.AppendTriangle(FIndex3i(VertexId3, VertexId4, VertexId5));
	Mesh.AppendTriangle(FIndex3i(VertexId4, VertexId2, VertexId5));
}


