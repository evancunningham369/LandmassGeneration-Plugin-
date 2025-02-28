// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Components/TerrainGeneratorComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTerrainGeneratorComponent() {}

// Begin Cross Module References
GEOMETRYFRAMEWORK_API UClass* Z_Construct_UClass_UDynamicMeshComponent();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ULandmassManagerSubsystem_NoRegister();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UTerrainGeneratorComponent();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UTerrainGeneratorComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class UTerrainGeneratorComponent
void UTerrainGeneratorComponent::StaticRegisterNativesUTerrainGeneratorComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTerrainGeneratorComponent);
UClass* Z_Construct_UClass_UTerrainGeneratorComponent_NoRegister()
{
	return UTerrainGeneratorComponent::StaticClass();
}
struct Z_Construct_UClass_UTerrainGeneratorComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "LOD LOD Mobility Trigger" },
		{ "IncludePath", "Components/TerrainGeneratorComponent.h" },
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShaderSubsystem_MetaData[] = {
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ShaderSubsystem;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTerrainGeneratorComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ShaderSubsystem = { "ShaderSubsystem", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTerrainGeneratorComponent, ShaderSubsystem), Z_Construct_UClass_ULandmassManagerSubsystem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShaderSubsystem_MetaData), NewProp_ShaderSubsystem_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTerrainGeneratorComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ShaderSubsystem,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainGeneratorComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UTerrainGeneratorComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDynamicMeshComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainGeneratorComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTerrainGeneratorComponent_Statics::ClassParams = {
	&UTerrainGeneratorComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UTerrainGeneratorComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainGeneratorComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainGeneratorComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UTerrainGeneratorComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTerrainGeneratorComponent()
{
	if (!Z_Registration_Info_UClass_UTerrainGeneratorComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTerrainGeneratorComponent.OuterSingleton, Z_Construct_UClass_UTerrainGeneratorComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTerrainGeneratorComponent.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<UTerrainGeneratorComponent>()
{
	return UTerrainGeneratorComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTerrainGeneratorComponent);
UTerrainGeneratorComponent::~UTerrainGeneratorComponent() {}
// End Class UTerrainGeneratorComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTerrainGeneratorComponent, UTerrainGeneratorComponent::StaticClass, TEXT("UTerrainGeneratorComponent"), &Z_Registration_Info_UClass_UTerrainGeneratorComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTerrainGeneratorComponent), 1172395237U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_40456859(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
