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
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALandmassManagerWrapper>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
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
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
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
		{ Z_Construct_UClass_ALandmassManagerWrapper, ALandmassManagerWrapper::StaticClass, TEXT("ALandmassManagerWrapper"), &Z_Registration_Info_UClass_ALandmassManagerWrapper, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALandmassManagerWrapper), 534752071U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManagerWrapper_h_2042981481(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManagerWrapper_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Manager_LandmassManagerWrapper_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
