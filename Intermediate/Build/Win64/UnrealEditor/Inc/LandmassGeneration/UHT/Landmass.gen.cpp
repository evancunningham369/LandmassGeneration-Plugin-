// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Landmass/Landmass.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLandmass() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ALandmass();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ALandmass_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class ALandmass
void ALandmass::StaticRegisterNativesALandmass()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALandmass);
UClass* Z_Construct_UClass_ALandmass_NoRegister()
{
	return ALandmass::StaticClass();
}
struct Z_Construct_UClass_ALandmass_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Landmass/Landmass.h" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALandmass>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ALandmass_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALandmass_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALandmass_Statics::ClassParams = {
	&ALandmass::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALandmass_Statics::Class_MetaDataParams), Z_Construct_UClass_ALandmass_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ALandmass()
{
	if (!Z_Registration_Info_UClass_ALandmass.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALandmass.OuterSingleton, Z_Construct_UClass_ALandmass_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALandmass.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<ALandmass>()
{
	return ALandmass::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ALandmass);
ALandmass::~ALandmass() {}
// End Class ALandmass

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALandmass, ALandmass::StaticClass, TEXT("ALandmass"), &Z_Registration_Info_UClass_ALandmass, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALandmass), 2190773671U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_2530321443(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
