// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Components/LandmassComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLandmassComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ULandmassComponent();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ULandmassComponent_NoRegister();
PROCEDURALMESHCOMPONENT_API UClass* Z_Construct_UClass_UProceduralMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class ULandmassComponent
void ULandmassComponent::StaticRegisterNativesULandmassComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULandmassComponent);
UClass* Z_Construct_UClass_ULandmassComponent_NoRegister()
{
	return ULandmassComponent::StaticClass();
}
struct Z_Construct_UClass_ULandmassComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "Components/LandmassComponent.h" },
		{ "ModuleRelativePath", "Components/LandmassComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProceduralMesh_MetaData[] = {
		{ "Category", "LandmassComponent" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Components/LandmassComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GridCellSize_MetaData[] = {
		{ "Category", "LandmassComponent" },
		{ "ModuleRelativePath", "Components/LandmassComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUsePerlinNoise_MetaData[] = {
		{ "Category", "LandmassComponent" },
		{ "ModuleRelativePath", "Components/LandmassComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProceduralMesh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GridCellSize;
	static void NewProp_bUsePerlinNoise_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUsePerlinNoise;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULandmassComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULandmassComponent_Statics::NewProp_ProceduralMesh = { "ProceduralMesh", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULandmassComponent, ProceduralMesh), Z_Construct_UClass_UProceduralMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProceduralMesh_MetaData), NewProp_ProceduralMesh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ULandmassComponent_Statics::NewProp_GridCellSize = { "GridCellSize", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULandmassComponent, GridCellSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GridCellSize_MetaData), NewProp_GridCellSize_MetaData) };
void Z_Construct_UClass_ULandmassComponent_Statics::NewProp_bUsePerlinNoise_SetBit(void* Obj)
{
	((ULandmassComponent*)Obj)->bUsePerlinNoise = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ULandmassComponent_Statics::NewProp_bUsePerlinNoise = { "bUsePerlinNoise", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ULandmassComponent), &Z_Construct_UClass_ULandmassComponent_Statics::NewProp_bUsePerlinNoise_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUsePerlinNoise_MetaData), NewProp_bUsePerlinNoise_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULandmassComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULandmassComponent_Statics::NewProp_ProceduralMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULandmassComponent_Statics::NewProp_GridCellSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULandmassComponent_Statics::NewProp_bUsePerlinNoise,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ULandmassComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USceneComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULandmassComponent_Statics::ClassParams = {
	&ULandmassComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ULandmassComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_ULandmassComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ULandmassComponent()
{
	if (!Z_Registration_Info_UClass_ULandmassComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULandmassComponent.OuterSingleton, Z_Construct_UClass_ULandmassComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULandmassComponent.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<ULandmassComponent>()
{
	return ULandmassComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ULandmassComponent);
ULandmassComponent::~ULandmassComponent() {}
// End Class ULandmassComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_LandmassComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULandmassComponent, ULandmassComponent::StaticClass, TEXT("ULandmassComponent"), &Z_Registration_Info_UClass_ULandmassComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULandmassComponent), 2969223747U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_LandmassComponent_h_3684838887(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_LandmassComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_LandmassComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
