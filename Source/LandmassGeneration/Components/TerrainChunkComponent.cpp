// Fill out your copyright notice in the Description page of Project Settings.
#include "TerrainChunkComponent.h"
#include "DynamicMesh/MeshNormals.h"
#include <LandmassGeneration/DebugMacros.h>

using namespace UE::Geometry;

UTerrainChunkComponent::UTerrainChunkComponent()
{
    SetComponentTickEnabled(false);
    SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SetCollisionObjectType(ECC_GameTraceChannel1);
}

void UTerrainChunkComponent::UpdateMeshFromSharedData()
{
    if (!ChunkData.IsValid())
    {
        return;
    }
    UpdateMesh(ChunkData->Triangles, ChunkData->TriangleCount);
}

void UTerrainChunkComponent::UpdateMesh(const TArray<FTriangle>& Triangles, uint32 TriangleCount)
{
    UE_LOG(LogTemp, Warning, TEXT("Updating mesh with %d triangles"), TriangleCount);
    // Start timing the mesh generation
    double StartTime = FPlatformTime::Seconds();

    // Clear the existing mesh
    Mesh.Clear();

    // Map to store unique vertices and their indices
    TMap<FVector, int32> UniqueVertices;

    // Scale factor for visualization - making this explicit
    const float VisualizationScale = 100.0f;

    // First pass: collect all unique vertices
    for (int32 i = 0; i < Triangles.Num(); i++)
    {
        const FTriangle& Triangle = Triangles[i];

        // Convert to FVector and apply scale
        FVector Vertex1(Triangle.Vertex1 * VisualizationScale);
        FVector Vertex2(Triangle.Vertex2 * VisualizationScale);
        FVector Vertex3(Triangle.Vertex3 * VisualizationScale);

        // Store unique vertices (no debug visualization for performance)
        if (!UniqueVertices.Contains(Vertex1))
        {
            UniqueVertices.Add(Vertex1, Mesh.AppendVertex(Vertex1));
        }

        if (!UniqueVertices.Contains(Vertex2))
        {
            UniqueVertices.Add(Vertex2, Mesh.AppendVertex(Vertex2));
        }

        if (!UniqueVertices.Contains(Vertex3))
        {
            UniqueVertices.Add(Vertex3, Mesh.AppendVertex(Vertex3));
        }

        // Add the triangle using vertex indices
        Mesh.AppendTriangle(
            UniqueVertices[Vertex1],
            UniqueVertices[Vertex2],
            UniqueVertices[Vertex3]
        );
    }

	//Iterate over Mesh vertices
  //  for (int32 VertexIndex = 0; VertexIndex < Mesh.MaxVertexID(); VertexIndex++)
  //  {
		//// Get the vertex position
		//FVector3d VertexPosition = Mesh.GetVertex(VertexIndex);
		//DRAW_POINT_PERM(VertexPosition, FColor::Red);
		//UE_LOG(LogTemp, Warning, TEXT("Vertex Index: %d, Vertex Position: %s"), VertexIndex ,*VertexPosition.ToString());
  //  }

    // Calculate normals for proper lighting/shading
    FMeshNormals::QuickComputeVertexNormals(Mesh);
    
    // Set the mesh to the component
    SetMesh(MoveTemp(Mesh));

    // Measure and log performance
    double EndTime = FPlatformTime::Seconds();
    UE_LOG(LogTemp, Warning, TEXT("Chunk mesh generation took %f seconds"), EndTime - StartTime);
    UE_LOG(LogTemp, Warning, TEXT("Unique vertices: %d"), UniqueVertices.Num());
}
