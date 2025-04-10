// Fill out your copyright notice in the Description page of Project Settings.


#include "GrassGeneratorComponent.h"
#include "TerrainGeneratorComponent.h"
#include "Engine/World.h"
#include "RenderingThread.h"
#include "PrimitiveViewRelevance.h"
#include "PrimitiveSceneProxy.h"
#include "RenderResource.h"
#include "RHI.h"
#include "RHIResources.h"
#include "ShaderParameterUtils.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "LandmassGeneration/DebugMacros.h"
#include "Kismet/GameplayStatics.h"

struct FGrassRenderData
{
	// Instanced mesh data
	UStaticMesh* GrassMesh;
	UMaterialInterface* GrassMaterial;

	// Compute shader resources
	FBufferRHIRef InstanceBuffer;
	FUnorderedAccessViewRHIRef InstancedBufferUAV;
	FShaderResourceViewRHIRef InstanceBufferSRV;

	// Counters for instance count
	FBufferRHIRef CounterBuffer;
	FUnorderedAccessViewRHIRef CounterBufferUAV;

	// Paramters
	float Density;
	FVector MinScale;
	FVector MaxScale;
	float MaxSlope;
	bool bRandomRotation;
	float CullDistance;

	// Number of instances
	int32 MaxInstances;

	FGrassRenderData() : GrassMesh(nullptr), GrassMaterial(nullptr),
		Density(0.0.f), MinScale(FVector::ZeroVector), MaxScale(FVector::ZeroVector),
		MaxSlope(45.0f), bRandomRotation(true), CullDistance(10000.0f), MaxInstances(0)
	{ }
};

// Grass component (one per grass type)
class FGrassComponent
{
public:
	FGrassComponent(const FGrassType& InGrassType, int32 InMaxInstances)
		: RenderData()
	{
		// Set up from grass type
		RenderData.GrassMesh = InGrassType.GrassMesh;
		RenderData.GrassMaterial = InGrassType.GrassMaterial;
		RenderData.Density = InGrassType.Density;
		RenderData.MinScale = InGrassType.MinScale;
		RenderData.MaxScale = InGrassType.MaxScale;
		RenderData.MaxSlope = InGrassType.MaxSlope;
		RenderData.bRandomRotation = InGrassType.bRandomRotation;
		RenderData.CullDistance = InGrassType.CullDistance;
		RenderData.MaxInstances = InMaxInstances;
	}
	
	~FGrassComponent()
	{
		ReleaseResources();
	}

	void InitResources()
	{
		if (!IsValid(RenderData.GrassMesh) || !IsValid(RenderData.GrassMaterial))
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot initialize grass resources - invalid mesh or material"));
			return;
		}

		// Create resources on render thread
		ENQUEUE_RENDER_COMMAND(InitGrassResources)(
			[this](FRHICommandListImmediate& RHICmdList)
			{
				// Create instance buffer (position, rotation, scale, etc)
				const uint32 InstanceSize = sizeof(FMatrix);
				FRHIResourceCreateInfo CreateInfo(TEXT("GrassInstanceBuffer"));

				// Use RHICmdList to create structured buffer
				RenderData.InstanceBuffer = RHICmdList.CreateStructuredBuffer(
					InstanceSize,
					InstanceSize * RenderData.MaxInstances,
					BUF_UnorderedAccess | BUF_ShaderResource,
					CreateInfo
				);

				// Create UAV
				RenderData.InstancedBufferUAV = RHICmdList.CreateUnorderedAccessView(
					RenderData.InstanceBuffer,
					FRHIViewDesc::CreateBufferUAV()
					.SetType(FRHIViewDesc::EBufferType::Structured)
				);

				// Create SRV
				RenderData.InstanceBufferSRV = RHICmdList.CreateShaderResourceView(
					RenderData.InstanceBuffer,
					FRHIViewDesc::CreateBufferSRV()
					.SetType(FRHIViewDesc::EBufferType::Structured)
					.SetStride(InstanceSize)
				);

				// Create counter buffer
				FRHIResourceCreateInfo CounterBufferCreateInfo(TEXT("GrassCounterBuffer"));
				RenderData.CounterBuffer = RHICmdList.CreateBuffer(
					sizeof(uint32),
					BUF_UnorderedAccess,
					sizeof(uint32),
					ERHIAccess::UAVCompute,
					CounterBufferCreateInfo
				);

				// Create counter UAV
				RenderData.CounterBufferUAV = RHICmdList.CreateUnorderedAccessView(
					RenderData.CounterBuffer,
					FRHIViewDesc::CreateBufferUAV()
					.SetType(FRHIViewDesc::EBufferType::Typed)
					.SetFormat(PF_R32_UINT)
				);

				// Clear counter
				uint32 ClearValue = 0;
				RHICmdList.ClearUAVUint(RenderData.CounterBufferUAV, FUintVector4(ClearValue, ClearValue, ClearValue, ClearValue));
			});
	}
	void ReleaseResources()
	{
		// Release resources on render thread
		ENQUEUE_RENDER_COMMAND(ReleaseGrassResources)(
			[this](FRHICommandListImmediate& RHICmdList)
			{
				RenderData.InstancedBufferUAV.SafeRelease();
				RenderData.InstanceBufferSRV.SafeRelease();
				RenderData.InstanceBuffer.SafeRelease();
				RenderData.CounterBufferUAV.SafeRelease();
				RenderData.CounterBuffer.SafeRelease();
			});
	}

	const FGrassRenderData& GetRenderData() const { return RenderData; }

private:
	FGrassRenderData RenderData;
};

// Render proxy for the grass component
class FGrassRenderProxy : public FPrimitiveSceneProxy
{
public:
	FGrassRenderProxy(const UGrassGeneratorComponent* InComponent)
		: FPrimitiveSceneProxy(InComponent)
		, Component(InComponent)
		, MaterialRelevance(InComponent->GetMaterialRelevance(GetScene().GetFeatureLevel()))
	{
		// Impelementation
	}

	virtual ~FGrassRenderProxy()
	{
		// Clean up resources if needed
	}

	virtual void GetDynamicMeshElements(
		const TArray<const FSceneView*>& Views,
		const FSceneViewFamily& ViewFamily,
		uint32 VisibilityMap,
		FMeshElementCollector& Collector) const override
	{
		// This is where you would add the mesh elements for rendering
		// A complete implementation would build draw calls for the grass instances
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
	{
		FPrimitiveViewRelevance Result;
		Result.bDrawRelevance = IsShown(View);
		Result.bDynamicRelevance = true;
		Result.bShadowRelevance = IsShadowCast(View);
		Result.bRenderInMainPass = ShouldRenderInMainPass();
		Result.bUsesLightingChannels = GetLightingChannelMask() != GetDefaultLightingChannelMask();
		Result.bRenderCustomDepth = ShouldRenderCustomDepth();
		MaterialRelevance.SetPrimitiveViewRelevance(Result);
		return Result;
	}

	virtual bool CanBeOccluded() const override
	{
		return !MaterialRelevance.bDisableDepthTest;
	}

	virtual uint32 GetMemoryFootprint() const override
	{
		return sizeof(*this) + GetAllocatedSize();
	}

	uint32 GetAllocatedSize() const
	{
		return FPrimitiveSceneProxy::GetAllocatedSize();
	}

	void UpdateGrassComponents(const TArray<TSharedPtr<FGrassComponent>>& InGrassComponents)
	{
		// Update the grass components on the render thread
		ENQUEUE_RENDER_COMMAND(UpdateGrassComponents)(
			[this, GrassComponentsCopy = InGrassComponents](FRHICommandListImmediate& RHICmdList)
			{
				this->GrassComponents = GrassComponentsCopy;
			});
	}

private:
	const UGrassGeneratorComponent* Component;
	FMaterialRelevance MaterialRelevance;
	TArray<TSharedPtr<FGrassComponent>> GrassComponents;
};

// Sets default values for this component's properties
UGrassGeneratorComponent::UGrassGeneratorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Set default property values
	CellSize = 100.0f;
	MaxGrassInstances = 1000000;
	bUpdateWithTerrain = true;
	FadeStartDistance = 8000.0f;
	FadeEndDistance = 10000.0f;
	DensityMultiplier = 1.0f;
	WindStrength = 1.0f;
	RandomSeed = 1337;
}

void UGrassGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Find and cache the terrain generator
	TerrainGenerator = GetTerrainGenerator();

	//Initialize grass if we have valid grass types
	if (GrassTypes.Num() > 0)
	{
		GenerateGrass();
	}
}

void UGrassGeneratorComponent::OnRegister()
{
	Super::OnRegister();

	// Get terrain generator
	TerrainGenerator = GetTerrainGenerator();

	if (!GrassRenderProxy)
	{
		GrassRenderProxy = MakeShared<FGrassRenderProxy>(this);
	}

	//Setup render resources
	SetupRenderResources();
}

void UGrassGeneratorComponent::OnUnregister()
{
	// Release render resources
	ReleaseRenderResources();

	// Clear render proxy
	GrassRenderProxy.Reset();

	Super::OnUnregister();
}

void UGrassGeneratorComponent::SendRenderDynamicData_Concurrent()
{
	Super::SendRenderDynamicData_Concurrent();

	// Update the grass render proxy with our components
	if (GrassRenderProxy)
	{
		GrassRenderProxy->UpdateGrassComponents(GrassComponents);
	}
}

void UGrassGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update camera position for LOD calculations
	if (UWorld* World = GetWorld())
	{
		if (APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(World, 0))
		{
			FVector NewCameraPosition = CameraManager->GetCameraLocation();

			// Update LOD if camera moved significantly
			float CameraMoveDistance = FVector::Distance(NewCameraPosition, CameraPosition);
			if (CameraMoveDistance > CellSize)
			{
				CameraPosition = NewCameraPosition;
				UpdateShaderParameters();
			}
		}
	}

	// Check if we need to regenerate grass
	if (bNeedsRegeneration)
	{
		bNeedsRegeneration = false;

		// In a full implementation, this would trigger the compute shader for grass placement
		// For now, we'll just log that regeneration would happen
		UE_LOG(LogTemp, Warning, TEXT("Grass regeneration would happen here"));
	}
}

void UGrassGeneratorComponent::GenerateGrass()
{
	UE_LOG(LogTemp, Warning, TEXT("GrassGeneratorComponent: Generating grass..."));

	// Clear existing grass components
	GrassComponents.Empty();

	// Make sure terrain generator is valid
	TerrainGenerator = GetTerrainGenerator();
	if (!TerrainGenerator)
	{
		UE_LOG(LogTemp, Warning, TEXT("GrassGeneratorComponent: No terrain generator found"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("GrassGeneratorComponent: Found TerrainGenerator"));

	// Create grass components for each grass type
	for (int32 TypeIndex = 0; TypeIndex < GrassTypes.Num(); TypeIndex)
	{
		const FGrassType& GrassType = GrassTypes[TypeIndex];

		// Skip if the grass mesh or material is invalid
		if (!GrassType.GrassMesh || !GrassType.GrassMaterial)
		{
			UE_LOG(LogTemp, Warning, TEXT("GrassGeneratorComponent: Invalid grass mesh or material for type %d"), TypeIndex);
			continue;
		}

		// Create grass component
		TSharedPtr<FGrassComponent> GrassComponent = MakeShared<FGrassComponent>(GrassType, MaxGrassInstances);
		GrassComponents.Add(GrassComponent);

		UE_LOG(LogTemp, Warning, TEXT("GrassGeneratorComponent: Created grass component for type %d"), TypeIndex);
	}

	// Initialize render resources
	SetupRenderResources();

	// Mark for regeneration
	bNeedsRegeneration = true;

	// Update the render proxy
	MarkRenderDynamicDataDirty();
}

UTerrainGeneratorComponent* UGrassGeneratorComponent::GetTerrainGenerator() const
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return nullptr;
	}

	return Owner->FindComponentByClass<UTerrainGeneratorComponent>();
}

void UGrassGeneratorComponent::UpdateShaderParameters()
{
	// Here we would update the shader parameters on the render thread
	// This includes camera position, density multiplier, wind strength, etc.

	// For now, we'll just mark for regeneration
	bNeedsRegeneration = true;
}

void UGrassGeneratorComponent::SetupRenderResources()
{
	if (bResourcesInitialized)
	{
		return;
	}

	// Initialize resources for each grass component
	for (TSharedPtr<FGrassComponent>& GrassComponent : GrassComponents)
	{
		GrassComponent->InitResources();
	}

	bResourcesInitialized = true;
}

void UGrassGeneratorComponent::ReleaseRenderResources()
{
	if (!bResourcesInitialized)
	{
		return;
	}

	// Release resources for each grass component
	for (TSharedPtr<FGrassComponent>& GrassComponent : GrassComponents)
	{
		GrassComponent->ReleaseResources();
	}

	bResourcesInitialized = false;
}




