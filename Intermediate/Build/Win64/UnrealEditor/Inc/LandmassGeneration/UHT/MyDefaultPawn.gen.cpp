// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Default/MyDefaultPawn.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyDefaultPawn() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_ADefaultPawn();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_AMyDefaultPawn();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_AMyDefaultPawn_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class AMyDefaultPawn
void AMyDefaultPawn::StaticRegisterNativesAMyDefaultPawn()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyDefaultPawn);
UClass* Z_Construct_UClass_AMyDefaultPawn_NoRegister()
{
	return AMyDefaultPawn::StaticClass();
}
struct Z_Construct_UClass_AMyDefaultPawn_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Default/MyDefaultPawn.h" },
		{ "ModuleRelativePath", "Default/MyDefaultPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Default/MyDefaultPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClickAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Default/MyDefaultPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EndDistance_MetaData[] = {
		{ "Category", "MyDefaultPawn" },
		{ "ModuleRelativePath", "Default/MyDefaultPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExplosionRadius_MetaData[] = {
		{ "Category", "MyDefaultPawn" },
		{ "ModuleRelativePath", "Default/MyDefaultPawn.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ClickAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EndDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ExplosionRadius;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyDefaultPawn>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyDefaultPawn_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyDefaultPawn, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContext_MetaData), NewProp_DefaultMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyDefaultPawn_Statics::NewProp_ClickAction = { "ClickAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyDefaultPawn, ClickAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClickAction_MetaData), NewProp_ClickAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyDefaultPawn_Statics::NewProp_EndDistance = { "EndDistance", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyDefaultPawn, EndDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EndDistance_MetaData), NewProp_EndDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyDefaultPawn_Statics::NewProp_ExplosionRadius = { "ExplosionRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyDefaultPawn, ExplosionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExplosionRadius_MetaData), NewProp_ExplosionRadius_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyDefaultPawn_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyDefaultPawn_Statics::NewProp_DefaultMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyDefaultPawn_Statics::NewProp_ClickAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyDefaultPawn_Statics::NewProp_EndDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyDefaultPawn_Statics::NewProp_ExplosionRadius,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyDefaultPawn_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMyDefaultPawn_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ADefaultPawn,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyDefaultPawn_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyDefaultPawn_Statics::ClassParams = {
	&AMyDefaultPawn::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AMyDefaultPawn_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AMyDefaultPawn_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyDefaultPawn_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyDefaultPawn_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMyDefaultPawn()
{
	if (!Z_Registration_Info_UClass_AMyDefaultPawn.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyDefaultPawn.OuterSingleton, Z_Construct_UClass_AMyDefaultPawn_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyDefaultPawn.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<AMyDefaultPawn>()
{
	return AMyDefaultPawn::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMyDefaultPawn);
AMyDefaultPawn::~AMyDefaultPawn() {}
// End Class AMyDefaultPawn

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Default_MyDefaultPawn_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyDefaultPawn, AMyDefaultPawn::StaticClass, TEXT("AMyDefaultPawn"), &Z_Registration_Info_UClass_AMyDefaultPawn, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyDefaultPawn), 1727949166U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Default_MyDefaultPawn_h_2593598748(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Default_MyDefaultPawn_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Default_MyDefaultPawn_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
