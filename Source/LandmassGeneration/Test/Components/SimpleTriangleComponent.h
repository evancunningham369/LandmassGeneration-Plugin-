#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SimpleTriangleComponent.generated.h"

UCLASS(ClassGroup = (LandmassGeneration), meta = (BlueprintSpawnableComponent))
class LANDMASSGENERATION_API USimpleTriangleComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USimpleTriangleComponent();

    void DrawGrassInstances();
};