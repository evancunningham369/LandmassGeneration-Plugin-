// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "LandmassGeneration/LandmassStructs.h"
#include "GrassGeneratorComponent.generated.h"

/**
 * Component responsible for generating and managing grass using GPU compute
 */
UCLASS(ClassGroup = (LandmassGeneration), meta = (BlueprintSpawnableComponent))
class LANDMASSGENERATION_API UGrassGeneratorComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UGrassGeneratorComponent();
    
    void DrawGrassInstances();
};
