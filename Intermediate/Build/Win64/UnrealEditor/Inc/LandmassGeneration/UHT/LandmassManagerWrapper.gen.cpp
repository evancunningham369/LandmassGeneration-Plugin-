// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Manager/LandmassManagerWrapper.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLandmassManagerWrapper() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
GEOMETRYFRAMEWORK_API UClass* Z_Construct_UClass_UDynamicMeshComponent_NoRegister();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ALandmassManagerWrapper();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ALandmassManagerWrapper_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class ALandmassManagerWrapper
void ALandmassManagerWrapper::StaticRegisterNativesALandmassManagerWrapper()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALandmassManagerWrapper);
UClass* Z_Construct_UClass_ALandmassManagerWrapper_NoRegister()
{
	return ALandmassManagerWrapper::StaticClass();
}
struct Z_Construct_UClass_ALandmassManagerWrapper_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Manager/LandmassManagerWrapper.h" },
		{ "ModuleRelativePath", "Manager/LandmassManagerWrapper.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DynamicMesh_MetaData[] = {
		{ "Category", "LandmassManagerWrapper" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Manager/LandmassManagerWrapper.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Material_MetaData[] = {
		{ "Category", "LandmassManagerWrapper" },
		{ "ModuleRelativePath", "Manager/LandmassManagerWrapper.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DynamicMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Material;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALandmassManagerWrapper>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALandmassManagerWrapper_Statics::NewProp_DynamicMesh = { "DynamicMesh", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmassManagerWrapper, DynamicMesh), Z_Construct_UClass_UDynamicMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DynamicMesh_MetaData), NewProp_DynamicMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALandmassManagerWrapper_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmassManagerWrapper, Material), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Material_MetaData), NewProp_Material_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALandmassManagerWrapper_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmassManagerWrapper_Statics::NewProp_DynamicMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmassManagerWrapper_Statics::NewProp_Material,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALandmassManagerWrapper_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ALandmassManagerWrapper_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALandmassManagerWrapper_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALandmassManagerWrapper_Statics::ClassParams = {
	&ALandmassManagerWrapper::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ALandmassManagerWrapper_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ALandmassManagerWrapper_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALandmassManagerWrapper_Statics::Class_MetaDataParams), Z_Construct_UClass_ALandmassManagerWrapper_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ALandmassManagerWrapper()
{
	if (!Z_Registration_Info_UClass_ALandmassManagerWrapper.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALandmassManagerWrapper.OuterSingleton, Z_Construct_UClass_ALandmassManagerWrapper_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALandmassManagerWrapper.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<ALandmassManagerWrapper>()
{
	return ALandmassManagerWrapper::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ALandmassManagerWrapper);
ALandmassManagerWrapper::~ALandmassManagerWrapper() {}
// End Class ALandmassManagerWrapper

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManagerWrapper_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALandmassManagerWrapper, ALandmassManagerWrapper::StaticClass, TEXT("ALandmassManagerWrapper"), &Z_Registration_Info_UClass_ALandmassManagerWrapper, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALandmassManagerWrapper), 2992942630U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManagerWrapper_h_1697207868(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManagerWrapper_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManagerWrapper_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
