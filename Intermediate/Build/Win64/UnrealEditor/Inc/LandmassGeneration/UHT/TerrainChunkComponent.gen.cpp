// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Components/TerrainChunkComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTerrainChunkComponent() {}

// Begin Cross Module References
GEOMETRYFRAMEWORK_API UClass* Z_Construct_UClass_UDynamicMeshComponent();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UTerrainChunkComponent();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UTerrainChunkComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class UTerrainChunkComponent
void UTerrainChunkComponent::StaticRegisterNativesUTerrainChunkComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTerrainChunkComponent);
UClass* Z_Construct_UClass_UTerrainChunkComponent_NoRegister()
{
	return UTerrainChunkComponent::StaticClass();
}
struct Z_Construct_UClass_UTerrainChunkComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "LOD LOD Mobility Trigger" },
		{ "IncludePath", "Components/TerrainChunkComponent.h" },
		{ "ModuleRelativePath", "Components/TerrainChunkComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTerrainChunkComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UTerrainChunkComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDynamicMeshComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainChunkComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTerrainChunkComponent_Statics::ClassParams = {
	&UTerrainChunkComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainChunkComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UTerrainChunkComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTerrainChunkComponent()
{
	if (!Z_Registration_Info_UClass_UTerrainChunkComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTerrainChunkComponent.OuterSingleton, Z_Construct_UClass_UTerrainChunkComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTerrainChunkComponent.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<UTerrainChunkComponent>()
{
	return UTerrainChunkComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTerrainChunkComponent);
UTerrainChunkComponent::~UTerrainChunkComponent() {}
// End Class UTerrainChunkComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainChunkComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTerrainChunkComponent, UTerrainChunkComponent::StaticClass, TEXT("UTerrainChunkComponent"), &Z_Registration_Info_UClass_UTerrainChunkComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTerrainChunkComponent), 2822575745U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainChunkComponent_h_3296533652(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainChunkComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainChunkComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
