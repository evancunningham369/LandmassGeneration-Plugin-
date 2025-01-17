// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Landmass/LandmassTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLandmassTypes() {}

// Begin Cross Module References
LANDMASSGENERATION_API UEnum* Z_Construct_UEnum_LandmassGeneration_ELandmassType();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Enum ELandmassType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ELandmassType;
static UEnum* ELandmassType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ELandmassType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ELandmassType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LandmassGeneration_ELandmassType, (UObject*)Z_Construct_UPackage__Script_LandmassGeneration(), TEXT("ELandmassType"));
	}
	return Z_Registration_Info_UEnum_ELandmassType.OuterSingleton;
}
template<> LANDMASSGENERATION_API UEnum* StaticEnum<ELandmassType>()
{
	return ELandmassType_StaticEnum();
}
struct Z_Construct_UEnum_LandmassGeneration_ELandmassType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ECS_MAX.DisplayName", "DefaultMAX" },
		{ "ECS_MAX.Name", "ELandmassType::ECS_MAX" },
		{ "ELMT_BottomEdge.DisplayName", "Bottom Edge" },
		{ "ELMT_BottomEdge.Name", "ELandmassType::ELMT_BottomEdge" },
		{ "ELMT_BottomLeft.DisplayName", "Bottom Left Corner" },
		{ "ELMT_BottomLeft.Name", "ELandmassType::ELMT_BottomLeft" },
		{ "ELMT_BottomRight.DisplayName", "Bottom Right Corner" },
		{ "ELMT_BottomRight.Name", "ELandmassType::ELMT_BottomRight" },
		{ "ELMT_LeftEdge.DisplayName", "Left Edge" },
		{ "ELMT_LeftEdge.Name", "ELandmassType::ELMT_LeftEdge" },
		{ "ELMT_Middle.DisplayName", "Middle" },
		{ "ELMT_Middle.Name", "ELandmassType::ELMT_Middle" },
		{ "ELMT_RightEdge.DisplayName", "Right Edge" },
		{ "ELMT_RightEdge.Name", "ELandmassType::ELMT_RightEdge" },
		{ "ELMT_TopEdge.DisplayName", "Top Edge" },
		{ "ELMT_TopEdge.Name", "ELandmassType::ELMT_TopEdge" },
		{ "ELMT_TopLeft.DisplayName", "Top Left Corner" },
		{ "ELMT_TopLeft.Name", "ELandmassType::ELMT_TopLeft" },
		{ "ELMT_TopRight.DisplayName", "Top Right Corner" },
		{ "ELMT_TopRight.Name", "ELandmassType::ELMT_TopRight" },
		{ "ModuleRelativePath", "Landmass/LandmassTypes.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ELandmassType::ELMT_BottomRight", (int64)ELandmassType::ELMT_BottomRight },
		{ "ELandmassType::ELMT_BottomLeft", (int64)ELandmassType::ELMT_BottomLeft },
		{ "ELandmassType::ELMT_TopLeft", (int64)ELandmassType::ELMT_TopLeft },
		{ "ELandmassType::ELMT_TopRight", (int64)ELandmassType::ELMT_TopRight },
		{ "ELandmassType::ELMT_Middle", (int64)ELandmassType::ELMT_Middle },
		{ "ELandmassType::ELMT_TopEdge", (int64)ELandmassType::ELMT_TopEdge },
		{ "ELandmassType::ELMT_LeftEdge", (int64)ELandmassType::ELMT_LeftEdge },
		{ "ELandmassType::ELMT_RightEdge", (int64)ELandmassType::ELMT_RightEdge },
		{ "ELandmassType::ELMT_BottomEdge", (int64)ELandmassType::ELMT_BottomEdge },
		{ "ELandmassType::ECS_MAX", (int64)ELandmassType::ECS_MAX },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LandmassGeneration_ELandmassType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_LandmassGeneration,
	nullptr,
	"ELandmassType",
	"ELandmassType",
	Z_Construct_UEnum_LandmassGeneration_ELandmassType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_LandmassGeneration_ELandmassType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_LandmassGeneration_ELandmassType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_LandmassGeneration_ELandmassType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_LandmassGeneration_ELandmassType()
{
	if (!Z_Registration_Info_UEnum_ELandmassType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ELandmassType.InnerSingleton, Z_Construct_UEnum_LandmassGeneration_ELandmassType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ELandmassType.InnerSingleton;
}
// End Enum ELandmassType

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_LandmassTypes_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ELandmassType_StaticEnum, TEXT("ELandmassType"), &Z_Registration_Info_UEnum_ELandmassType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2825973606U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_LandmassTypes_h_1787222659(TEXT("/Script/LandmassGeneration"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_LandmassTypes_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_LandmassTypes_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
