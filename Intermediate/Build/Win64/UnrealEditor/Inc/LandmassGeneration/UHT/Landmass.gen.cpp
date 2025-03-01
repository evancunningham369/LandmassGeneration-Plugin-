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
LANDMASSGENERATION_API UEnum* Z_Construct_UEnum_LandmassGeneration_ETerrainQuality();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Enum ETerrainQuality
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ETerrainQuality;
static UEnum* ETerrainQuality_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ETerrainQuality.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ETerrainQuality.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LandmassGeneration_ETerrainQuality, (UObject*)Z_Construct_UPackage__Script_LandmassGeneration(), TEXT("ETerrainQuality"));
	}
	return Z_Registration_Info_UEnum_ETerrainQuality.OuterSingleton;
}
template<> LANDMASSGENERATION_API UEnum* StaticEnum<ETerrainQuality>()
{
	return ETerrainQuality_StaticEnum();
}
struct Z_Construct_UEnum_LandmassGeneration_ETerrainQuality_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Custom.DisplayName", "Custom" },
		{ "Custom.Name", "ETerrainQuality::Custom" },
		{ "High.DisplayName", "High" },
		{ "High.Name", "ETerrainQuality::High" },
		{ "Low.DisplayName", "Low" },
		{ "Low.Name", "ETerrainQuality::Low" },
		{ "Medium.DisplayName", "Medium" },
		{ "Medium.Name", "ETerrainQuality::Medium" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
		{ "Ultra.DisplayName", "Ultra" },
		{ "Ultra.Name", "ETerrainQuality::Ultra" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ETerrainQuality::Low", (int64)ETerrainQuality::Low },
		{ "ETerrainQuality::Medium", (int64)ETerrainQuality::Medium },
		{ "ETerrainQuality::High", (int64)ETerrainQuality::High },
		{ "ETerrainQuality::Ultra", (int64)ETerrainQuality::Ultra },
		{ "ETerrainQuality::Custom", (int64)ETerrainQuality::Custom },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LandmassGeneration_ETerrainQuality_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_LandmassGeneration,
	nullptr,
	"ETerrainQuality",
	"ETerrainQuality",
	Z_Construct_UEnum_LandmassGeneration_ETerrainQuality_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_LandmassGeneration_ETerrainQuality_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_LandmassGeneration_ETerrainQuality_Statics::Enum_MetaDataParams), Z_Construct_UEnum_LandmassGeneration_ETerrainQuality_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_LandmassGeneration_ETerrainQuality()
{
	if (!Z_Registration_Info_UEnum_ETerrainQuality.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ETerrainQuality.InnerSingleton, Z_Construct_UEnum_LandmassGeneration_ETerrainQuality_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ETerrainQuality.InnerSingleton;
}
// End Enum ETerrainQuality

// Begin Class ALandmass Function RegenerateTerrain
struct Z_Construct_UFunction_ALandmass_RegenerateTerrain_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Terrain Generation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Regenerate terrain\n" },
#endif
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Regenerate terrain" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALandmass_RegenerateTerrain_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALandmass, nullptr, "RegenerateTerrain", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALandmass_RegenerateTerrain_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALandmass_RegenerateTerrain_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ALandmass_RegenerateTerrain()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALandmass_RegenerateTerrain_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ALandmass::execRegenerateTerrain)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RegenerateTerrain();
	P_NATIVE_END;
}
// End Class ALandmass Function RegenerateTerrain

// Begin Class ALandmass
void ALandmass::StaticRegisterNativesALandmass()
{
	UClass* Class = ALandmass::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "RegenerateTerrain", &ALandmass::execRegenerateTerrain },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TerrainQuality_MetaData[] = {
		{ "Category", "Terrain Generation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Quality presets\n" },
#endif
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Quality presets" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomTerrainWidth_MetaData[] = {
		{ "Category", "Terrain Generation" },
		{ "ClampMax", "512" },
		{ "ClampMin", "8" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Custom terrain settings (only used when TerrainQuality = Custom)\n" },
#endif
		{ "EditCondition", "TerrainQuality == ETerrainQuality::Custom" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Custom terrain settings (only used when TerrainQuality = Custom)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomTerrainHeight_MetaData[] = {
		{ "Category", "Terrain Generation" },
		{ "ClampMax", "512" },
		{ "ClampMin", "8" },
		{ "EditCondition", "TerrainQuality == ETerrainQuality::Custom" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomTerrainDepth_MetaData[] = {
		{ "Category", "Terrain Generation" },
		{ "ClampMax", "512" },
		{ "ClampMin", "8" },
		{ "EditCondition", "TerrainQuality == ETerrainQuality::Custom" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkSize_MetaData[] = {
		{ "Category", "Terrain Generation" },
		{ "ClampMax", "64" },
		{ "ClampMin", "8" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Chunk size\n" },
#endif
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Chunk size" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxTriangles_MetaData[] = {
		{ "Category", "Terrain Generation" },
		{ "ClampMax", "5000000" },
		{ "ClampMin", "10000" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Maximum number of triangles to generate\n" },
#endif
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum number of triangles to generate" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableDebugVisualization_MetaData[] = {
		{ "Category", "Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Debug visualization\n" },
#endif
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Debug visualization" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_TerrainQuality_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_TerrainQuality;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CustomTerrainWidth;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CustomTerrainHeight;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CustomTerrainDepth;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ChunkSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxTriangles;
	static void NewProp_bEnableDebugVisualization_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableDebugVisualization;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ALandmass_RegenerateTerrain, "RegenerateTerrain" }, // 2157241250
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALandmass>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_TerrainQuality_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_TerrainQuality = { "TerrainQuality", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmass, TerrainQuality), Z_Construct_UEnum_LandmassGeneration_ETerrainQuality, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TerrainQuality_MetaData), NewProp_TerrainQuality_MetaData) }; // 2861608630
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_CustomTerrainWidth = { "CustomTerrainWidth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmass, CustomTerrainWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomTerrainWidth_MetaData), NewProp_CustomTerrainWidth_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_CustomTerrainHeight = { "CustomTerrainHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmass, CustomTerrainHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomTerrainHeight_MetaData), NewProp_CustomTerrainHeight_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_CustomTerrainDepth = { "CustomTerrainDepth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmass, CustomTerrainDepth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomTerrainDepth_MetaData), NewProp_CustomTerrainDepth_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_ChunkSize = { "ChunkSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmass, ChunkSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkSize_MetaData), NewProp_ChunkSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_MaxTriangles = { "MaxTriangles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmass, MaxTriangles), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxTriangles_MetaData), NewProp_MaxTriangles_MetaData) };
void Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableDebugVisualization_SetBit(void* Obj)
{
	((ALandmass*)Obj)->bEnableDebugVisualization = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableDebugVisualization = { "bEnableDebugVisualization", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALandmass), &Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableDebugVisualization_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableDebugVisualization_MetaData), NewProp_bEnableDebugVisualization_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALandmass_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_TerrainQuality_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_TerrainQuality,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_CustomTerrainWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_CustomTerrainHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_CustomTerrainDepth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_ChunkSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_MaxTriangles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableDebugVisualization,
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
	FuncInfo,
	Z_Construct_UClass_ALandmass_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
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
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ETerrainQuality_StaticEnum, TEXT("ETerrainQuality"), &Z_Registration_Info_UEnum_ETerrainQuality, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2861608630U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALandmass, ALandmass::StaticClass, TEXT("ALandmass"), &Z_Registration_Info_UClass_ALandmass, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALandmass), 2789041612U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_4124716477(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
