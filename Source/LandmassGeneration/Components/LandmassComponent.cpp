// Fill out your copyright notice in the Description page of Project Settings.


#include "LandmassComponent.h"
#include "ProceduralMeshComponent.h"
#include "LandmassGeneration/Manager/LandmassManager.h"
#include "LandmassGeneration/DebugMacros.h"
#include "Components/DynamicMeshComponent.h"

ULandmassComponent::ULandmassComponent()
{
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	ProceduralMesh->SetupAttachment(this);

}

void ULandmassComponent::BeginPlay()
{
	Super::BeginPlay();	
	
}

void ULandmassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void ULandmassComponent::RemoveMesh(const FHitResult& HitResult, float Radius, const FVector& HitDirection)
{
	const FVector HitLocation = HitResult.Location;
	const FVector LocalHitLocation = ProceduralMesh->GetComponentTransform().InverseTransformPosition(HitLocation);

	//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Local Hit Location: %s\n\n\n"), *LocalHitLocation.ToString());

	ReCreateMesh(HitLocation, LocalHitLocation ,Radius);	
}

void ULandmassComponent::ReCreateMesh(const FVector& WorldHitLocation, const FVector& LocalHitLocation, float Radius)
{

	//float SquaredSphereRadius = Radius * Radius;

	//FColor RandomColor = FColor::MakeRandomColor();
	//for (int32 x = 0; x < Width; x++)
	//{
	//	for (int32 z = 1; z < Height; z++)
	//	{
	//		for (int32 y = 0; y < Width; y++)
	//		{
	//			FVector Vertex = (FVector(x, y, z) * 100) + LandmassOffset;
	//			if (FVector::DistSquared(Vertex, WorldHitLocation) <= SquaredSphereRadius)
	//			{
	//				//SetTerrainMapValue(x, y, z, 1.f);
	//			}
	//		}
	//	}
	//}
}

void ULandmassComponent::InitializeLandmassOffsets(FVector Offset)
{
	LandmassOffset = Offset;
	LandmassOffsetScaleDown = FIntVector(FMath::RoundToInt(Offset.X / 100), FMath::RoundToInt(Offset.Y / 100), FMath::RoundToInt(Offset.Z / 100));
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


