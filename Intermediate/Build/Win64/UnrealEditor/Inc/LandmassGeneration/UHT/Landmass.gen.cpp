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
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ULandmassComponent_NoRegister();
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LandmassComponent_MetaData[] = {
		{ "Category", "Landmass" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LandmassComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALandmass>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_LandmassComponent = { "LandmassComponent", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmass, LandmassComponent), Z_Construct_UClass_ULandmassComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LandmassComponent_MetaData), NewProp_LandmassComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALandmass_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_LandmassComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALandmass_Statics::PropPointers) < 2048);
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
	Z_Construct_UClass_ALandmass_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ALandmass_Statics::PropPointers),
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
		{ Z_Construct_UClass_ALandmass, ALandmass::StaticClass, TEXT("ALandmass"), &Z_Registration_Info_UClass_ALandmass, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALandmass), 2852583039U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_2859531112(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
