// Fill out your copyright notice in the Description page of Project Settings.

#include "LandmassGeneration.h"
#include "Modules/ModuleManager.h"

class FLandmassGenerationModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        UE_LOG(LogTemp, Warning, TEXT("LandmassGeneration Module Loaded!"));
        FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));
        AddShaderSourceDirectoryMapping("/Project", ShaderDirectory);
    }

    virtual void ShutdownModule() override
    {
        UE_LOG(LogTemp, Warning, TEXT("LandmassGeneration Module Unloaded!"));
    }
};

IMPLEMENT_MODULE(FLandmassGenerationModule, LandmassGeneration);