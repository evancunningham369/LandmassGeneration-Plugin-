// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "LandmassManagerWrapper.h"
#include "LandmassManager.h"
#include "LandmassGeneration/Shaders/LandmassComputeShader.h"

#include "RenderGraphUtils.h"           // RDG utility functions
#include "RenderGraphResources.h"       // RDG buffer and texture handling
#include "RenderGraphBuilder.h"         // Required for FRDGBuilder
#include "ShaderParameterUtils.h"       // Required for shader parameters
#include "RHIResources.h"               // Handles RHI buffers and resources


ALandmassManagerWrapper::ALandmassManagerWrapper()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

void ALandmassManagerWrapper::BeginPlay()
{
	Super::BeginPlay();

	ENQUEUE_RENDER_COMMAND(MyRenderCommand)(
		[this](FRHICommandListImmediate& RHICmdList)
		{
			// Get the global shader map
			TShaderMapRef<FMyComputeShader> MyComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
			if (!MyComputeShader.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("Compute Shader not valid!"))
				return;
			}
			// Use RDG for GPU resource management
			FRDGBuilder GraphBuilder(RHICmdList);

			// Create an RDG buffer for the compute shader
			FRDGBufferRef OutputBuffer = GraphBuilder.CreateBuffer(
				FRDGBufferDesc::CreateStructuredDesc(sizeof(int), 2),
				TEXT("OutputBuffer")
			);

			FRDGBufferUAVRef OutputBufferUAV = GraphBuilder.CreateUAV(OutputBuffer, PF_R32_UINT);

			// Allocate parameters
			FMyComputeShader::FParameters* PassParameters = GraphBuilder.AllocParameters<FMyComputeShader::FParameters>();
			PassParameters->OutputBufferUAV = OutputBufferUAV;

			// Dispatch the compute shader using FComputeShaderUtils
			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("ComputeShaderPass"),
				MyComputeShader,
				PassParameters,
				FIntVector(1, 1, 1)
			);

			FRHIGPUBufferReadback* ReadbackBuffer = new FRHIGPUBufferReadback(TEXT("ComputeReadback"));
			AddEnqueueCopyPass(GraphBuilder, ReadbackBuffer, OutputBuffer, 8); // Copy (n) bytes (uint32)

			// Execute the RDG Graph
			GraphBuilder.Execute();

			CheckReadbackBuffer(ReadbackBuffer);
			
		});
}

void ALandmassManagerWrapper::CheckReadbackBuffer(FRHIGPUBufferReadback* ReadbackBuffer)
{
	AsyncTask(ENamedThreads::ActualRenderingThread, [ReadbackBuffer, this]()
		{
			if (ReadbackBuffer->IsReady())
			{
				int32* Data = (int32*)ReadbackBuffer->Lock(8);
				AsyncTask(ENamedThreads::GameThread, [Data]()
					{
						UE_LOG(LogTemp, Warning, TEXT("Data: %d"), Data[0]);
						UE_LOG(LogTemp, Warning, TEXT("Data: %d"), Data[1]);
					});
				ReadbackBuffer->Unlock();
				delete ReadbackBuffer;
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, []()
					{
						UE_LOG(LogTemp, Warning, TEXT("Buffer readback not ready...retrying..."));
					});
				FPlatformProcess::Sleep(0.05f); // Small delay to avoid spamming logs
				CheckReadbackBuffer(ReadbackBuffer); // Re-check until ready
			}
		});
}

void ALandmassManagerWrapper::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UWorld* World = GetWorld();
	if (World)
	{
		if (NumOfChunksX <= 0 || NumOfChunksY <= 0) return;
		ULandmassManager::Get()->SpawnChunks(World, TerrainWidth, TerrainHeight, NumOfChunksX, NumOfChunksY, NumOfChunksZ ,TerrainMaterial);
		//ULandmassManager::Get()->SpawnChunk(World, TerrainWidth, TerrainHeight, TerrainMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("World is invalid"))
	}
}


