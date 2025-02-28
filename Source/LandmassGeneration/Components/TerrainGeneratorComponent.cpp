// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainGeneratorComponent.h"
#include <LandmassGeneration/Subsystems/LandmassManagerSubsystem.h>
#include "LandmassGeneration/DebugMacros.h"
#include <DynamicMesh/MeshNormals.h>

using namespace UE::Geometry;

UTerrainGeneratorComponent::UTerrainGeneratorComponent()
{
	SetComponentTickEnabled(false);

	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetCollisionObjectType(ECC_GameTraceChannel1);
}

void UTerrainGeneratorComponent::GenerateTerrain(const FTerrainGenerationParams& Params)
{
	TerrainParams = Params;

	if (!ShaderSubsystem)
	{
		ShaderSubsystem = GetWorld()->GetSubsystem<ULandmassManagerSubsystem>();
	}

	if (CurrentGenerationRequestId != INDEX_NONE)
	{
		ShaderSubsystem->CancelRequest(CurrentGenerationRequestId);
		CurrentGenerationRequestId = INDEX_NONE;
	}

	CurrentGenerationRequestId = ShaderSubsystem->RequestTerrainGeneration(
		TerrainParams,
		[this](const TArray<FTriangle>& Triangles, uint32 TriangleCount)
		{
			OnComputeShaderComplete(Triangles, TriangleCount);
		});
}

void UTerrainGeneratorComponent::OnComputeShaderComplete(const TArray<FTriangle>& Triangles, uint32 TriangleCount)
{
	UE_LOG(LogTemp, Warning, TEXT("Shader Completed!"));
	UE_LOG(LogTemp, Warning, TEXT("Triangle Count: %d"), TriangleCount);

	Mesh.Clear();
	for (int32 i = 0; i < Triangles.Num(); i++)
	{
		const FTriangle& Triangle = Triangles[i];
		FVector Vertex1(Triangle.Vertex1 * 100);
		FVector Vertex2(Triangle.Vertex2 * 100);
		FVector Vertex3(Triangle.Vertex3 * 100);
		UE_LOG(LogTemp, Warning, TEXT("Final Vertex1: %s"), *Triangle.Vertex1.ToString())
		UE_LOG(LogTemp, Warning, TEXT("Final Vertex2: %s"), *Triangle.Vertex2.ToString())
		UE_LOG(LogTemp, Warning, TEXT("Final Vertex3: %s"), *Triangle.Vertex3.ToString())

		DRAW_POINT_PERM(Vertex1, FColor::Blue);
		DRAW_POINT_PERM(Vertex2, FColor::Green);
		DRAW_POINT_PERM(Vertex3, FColor::Red);

		DRAW_LINE_PERM(Vertex1, Vertex2);
		DRAW_LINE_PERM(Vertex2, Vertex3);
		DRAW_LINE_PERM(Vertex3, Vertex1);


		int32 VertexId1 = Mesh.AppendVertex(Vertex1);
		int32 VertexId2 = Mesh.AppendVertex(Vertex2);
		int32 VertexId3 = Mesh.AppendVertex(Vertex3);

		Mesh.AppendTriangle(VertexId1, VertexId2, VertexId3);
	}
	FMeshNormals::QuickComputeVertexNormals(Mesh);
	SetMesh(MoveTemp(Mesh));
	
	CurrentGenerationRequestId = INDEX_NONE;
}

void UTerrainGeneratorComponent::DrawTriangle()
{
	int32 Vertex1 = Mesh.AppendVertex(FVector(0, 0, 0));
	int32 Vertex2 = Mesh.AppendVertex(FVector(100, 0, 0));
	int32 Vertex3 = Mesh.AppendVertex(FVector(100, 100, 0));

	DRAW_POINT_PERM(FVector(0, 0, 0), FColor::Red);

	Mesh.AppendTriangle(Vertex1, Vertex2, Vertex3);

	SetMesh(MoveTemp(Mesh));
}
