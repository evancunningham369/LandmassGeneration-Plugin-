#include "SimpleTriangleComponent.h"
#include "RenderResource.h"
#include "RHI.h"
#include "RHIResources.h"
#include "ShaderParameterUtils.h"
#include "RenderGraphBuilder.h"  
#include <LandmassGeneration/Test/Shaders/SimpleTriangleShaders.h>
#include "ShaderParameterStruct.h"
#include "Slate/SceneViewport.h" // Add this include to resolve the incomplete type error  

USimpleTriangleComponent::USimpleTriangleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

BEGIN_SHADER_PARAMETER_STRUCT(FSimpleTrianglePassParameters, )
	RDG_BUFFER_ACCESS(PositionBufferForStream, ERHIAccess::VertexOrIndexBuffer)
	RDG_BUFFER_ACCESS(ColorBufferForStream, ERHIAccess::VertexOrIndexBuffer)
	SHADER_PARAMETER_RDG_UNIFORM_BUFFER(FVertexShaderExample::FParameters, VSParams)
	SHADER_PARAMETER_RDG_UNIFORM_BUFFER(FPixelShaderExample::FParameters, PSParams)
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()

void USimpleTriangleComponent::DrawGrassInstances()
{
	FRHITexture* ViewportRT_RHI;
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->GetGameViewport())
	{
		ViewportRT_RHI = GEngine->GameViewport->GetGameViewport()->GetRenderTargetTexture();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Viewport not found!"));
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Drawing grass instances using RDG!"));
	ENQUEUE_RENDER_COMMAND(DrawTriangleRDGCommand)(
		[ViewportRT_RHI](FRHICommandListImmediate& RHICmdList)
		{
			FRDGBuilder GraphBuilder(RHICmdList);

			TArray<FVector3f> Positions;
			Positions.Add(FVector3f(0.0f, 100.f, 0.0f));
			Positions.Add(FVector3f(-100.f, -100.f, 0.0f));
			Positions.Add(FVector3f(100.f, -100.f, 0.0f));

			TArray<FLinearColor> Colors;
			Colors.Add(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
			Colors.Add(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
			Colors.Add(FLinearColor(0.0f, 0.0f, 1.0f, 1.0f));

			FRDGBufferDesc PositionBufferDesc = FRDGBufferDesc::CreateBufferDesc(
				sizeof(FVector3f), Positions.Num());
			
			FRDGBufferRef PositionBuffer = GraphBuilder.CreateBuffer(
				PositionBufferDesc, TEXT("TrianglePositionsBuffer")
			);

			FRDGBufferDesc ColorBufferDesc = FRDGBufferDesc::CreateBufferDesc(
				sizeof(FLinearColor), Colors.Num()
			);

			FRDGBufferRef ColorBuffer = GraphBuilder.CreateBuffer(
				ColorBufferDesc, TEXT("TriangleColorBuffer")
			);

			GraphBuilder.QueueBufferUpload(PositionBuffer, Positions.GetData(),
				Positions.NumBytes(), ERDGInitialDataFlags::NoCopy);

			GraphBuilder.QueueBufferUpload(ColorBuffer, Colors.GetData(),
				Colors.NumBytes(), ERDGInitialDataFlags::NoCopy);

			FVertexShaderExample::FParameters* VSParamsContents = GraphBuilder.AllocParameters<FVertexShaderExample::FParameters>();
			FPixelShaderExample::FParameters* PSParamsContents = GraphBuilder.AllocParameters<FPixelShaderExample::FParameters>();

			TRDGUniformBufferRef<FVertexShaderExample::FParameters> VSUniformBuffer =
				GraphBuilder.CreateUniformBuffer(VSParamsContents);
			TRDGUniformBufferRef<FPixelShaderExample::FParameters> PSUniformBuffer =
				GraphBuilder.CreateUniformBuffer(PSParamsContents);

			FRDGTextureRef RenderTarget = GraphBuilder.RegisterExternalTexture(
				CreateRenderTarget(ViewportRT_RHI, TEXT("RegisteredViewportRT"))
			);
			
			check(RenderTarget != nullptr);

			FMatrix ViewProjectionMatrix = FMatrix::Identity;

			VSParamsContents->ViewProjectionMatrix = FMatrix44f(ViewProjectionMatrix);
			PSParamsContents->Color = FVector4f(1.0f, 1.0f, 1.0f, 1.0f);

			FSimpleTrianglePassParameters* PassParameters = GraphBuilder.AllocParameters<FSimpleTrianglePassParameters>();

			PassParameters->PositionBufferForStream = PositionBuffer;
			PassParameters->ColorBufferForStream = ColorBuffer;
			PassParameters->VSParams = VSUniformBuffer;
			PassParameters->PSParams = PSUniformBuffer;
			PassParameters->RenderTargets[0] = FRenderTargetBinding(RenderTarget, ERenderTargetLoadAction::ELoad);

			GraphBuilder.AddPass(
				RDG_EVENT_NAME("DrawTriangle"),
				PassParameters,
				ERDGPassFlags::Raster,
				[PassParameters, PositionBuffer, ColorBuffer, ViewportRT_RHI](FRHICommandList& InRHICmdList)
				{

					TShaderMapRef<FVertexShaderExample> VertexShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
					TShaderMapRef<FPixelShaderExample> PixelShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

					FVertexDeclarationElementList Elements;
					Elements.Add(FVertexElement(0, 0, VET_Float3, 0, sizeof(FVector3f)));
					Elements.Add(FVertexElement(1, 0, VET_Float4, 1, sizeof(FLinearColor)));
					FVertexDeclarationRHIRef VertexDeclarationRHI =
						PipelineStateCache::GetOrCreateVertexDeclaration(Elements);
				
					
					FGraphicsPipelineStateInitializer GraphicsPSOInit;
					InRHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);

					GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
					GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid, CM_None>::GetRHI();
					GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
					GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = VertexDeclarationRHI;
					GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
					GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
					GraphicsPSOInit.PrimitiveType = PT_TriangleList;

					SetGraphicsPipelineState(InRHICmdList, GraphicsPSOInit, 0);
					
					InRHICmdList.SetStreamSource(0, PositionBuffer->GetRHI(), 0);
					InRHICmdList.SetStreamSource(1, ColorBuffer->GetRHI(), 0);

					InRHICmdList.DrawPrimitive(0, 1, 1);

				});
			GraphBuilder.Execute();
		});
}
