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

// Sets default values for this component's properties
UGrassGeneratorComponent::UGrassGeneratorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}



