// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Manager/LandmassManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLandmassManager() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ULandmassManager();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ULandmassManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class ULandmassManager
void ULandmassManager::StaticRegisterNativesULandmassManager()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULandmassManager);
UClass* Z_Construct_UClass_ULandmassManager_NoRegister()
{
	return ULandmassManager::StaticClass();
}
struct Z_Construct_UClass_ULandmassManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Manager/LandmassManager.h" },
		{ "ModuleRelativePath", "Manager/LandmassManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaterialTransitionMultiplier_MetaData[] = {
		{ "Category", "LandmassManager" },
		{ "ModuleRelativePath", "Manager/LandmassManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FDoublePropertyParams NewProp_MaterialTransitionMultiplier;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULandmassManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_ULandmassManager_Statics::NewProp_MaterialTransitionMultiplier = { "MaterialTransitionMultiplier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULandmassManager, MaterialTransitionMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaterialTransitionMultiplier_MetaData), NewProp_MaterialTransitionMultiplier_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULandmassManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULandmassManager_Statics::NewProp_MaterialTransitionMultiplier,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ULandmassManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULandmassManager_Statics::ClassParams = {
	&ULandmassManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ULandmassManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassManager_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassManager_Statics::Class_MetaDataParams), Z_Construct_UClass_ULandmassManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ULandmassManager()
{
	if (!Z_Registration_Info_UClass_ULandmassManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULandmassManager.OuterSingleton, Z_Construct_UClass_ULandmassManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULandmassManager.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<ULandmassManager>()
{
	return ULandmassManager::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ULandmassManager);
ULandmassManager::~ULandmassManager() {}
// End Class ULandmassManager

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManager_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULandmassManager, ULandmassManager::StaticClass, TEXT("ULandmassManager"), &Z_Registration_Info_UClass_ULandmassManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULandmassManager), 2726047630U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManager_h_2946931165(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManager_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
