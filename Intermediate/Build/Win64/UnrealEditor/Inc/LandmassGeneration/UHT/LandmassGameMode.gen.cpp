// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/GameModes/LandmassGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLandmassGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameMode();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ALandmassGameMode();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ALandmassGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class ALandmassGameMode
void ALandmassGameMode::StaticRegisterNativesALandmassGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALandmassGameMode);
UClass* Z_Construct_UClass_ALandmassGameMode_NoRegister()
{
	return ALandmassGameMode::StaticClass();
}
struct Z_Construct_UClass_ALandmassGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "GameModes/LandmassGameMode.h" },
		{ "ModuleRelativePath", "GameModes/LandmassGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALandmassGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ALandmassGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameMode,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALandmassGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALandmassGameMode_Statics::ClassParams = {
	&ALandmassGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALandmassGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ALandmassGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ALandmassGameMode()
{
	if (!Z_Registration_Info_UClass_ALandmassGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALandmassGameMode.OuterSingleton, Z_Construct_UClass_ALandmassGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALandmassGameMode.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<ALandmassGameMode>()
{
	return ALandmassGameMode::StaticClass();
}
ALandmassGameMode::ALandmassGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ALandmassGameMode);
ALandmassGameMode::~ALandmassGameMode() {}
// End Class ALandmassGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_GameModes_LandmassGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALandmassGameMode, ALandmassGameMode::StaticClass, TEXT("ALandmassGameMode"), &Z_Registration_Info_UClass_ALandmassGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALandmassGameMode), 3986051859U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_GameModes_LandmassGameMode_h_445366096(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_GameModes_LandmassGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_GameModes_LandmassGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
