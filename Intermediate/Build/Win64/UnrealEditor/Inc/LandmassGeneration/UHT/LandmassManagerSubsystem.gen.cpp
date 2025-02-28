// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Subsystems/LandmassManagerSubsystem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLandmassManagerSubsystem() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ULandmassManagerSubsystem();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ULandmassManagerSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class ULandmassManagerSubsystem
void ULandmassManagerSubsystem::StaticRegisterNativesULandmassManagerSubsystem()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULandmassManagerSubsystem);
UClass* Z_Construct_UClass_ULandmassManagerSubsystem_NoRegister()
{
	return ULandmassManagerSubsystem::StaticClass();
}
struct Z_Construct_UClass_ULandmassManagerSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Subsystems/LandmassManagerSubsystem.h" },
		{ "ModuleRelativePath", "Subsystems/LandmassManagerSubsystem.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULandmassManagerSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ULandmassManagerSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UWorldSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassManagerSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULandmassManagerSubsystem_Statics::ClassParams = {
	&ULandmassManagerSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULandmassManagerSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_ULandmassManagerSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ULandmassManagerSubsystem()
{
	if (!Z_Registration_Info_UClass_ULandmassManagerSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULandmassManagerSubsystem.OuterSingleton, Z_Construct_UClass_ULandmassManagerSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULandmassManagerSubsystem.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<ULandmassManagerSubsystem>()
{
	return ULandmassManagerSubsystem::StaticClass();
}
ULandmassManagerSubsystem::ULandmassManagerSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ULandmassManagerSubsystem);
ULandmassManagerSubsystem::~ULandmassManagerSubsystem() {}
// End Class ULandmassManagerSubsystem

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Subsystems_LandmassManagerSubsystem_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULandmassManagerSubsystem, ULandmassManagerSubsystem::StaticClass, TEXT("ULandmassManagerSubsystem"), &Z_Registration_Info_UClass_ULandmassManagerSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULandmassManagerSubsystem), 1112842515U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Subsystems_LandmassManagerSubsystem_h_3667946631(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Subsystems_LandmassManagerSubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Subsystems_LandmassManagerSubsystem_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
