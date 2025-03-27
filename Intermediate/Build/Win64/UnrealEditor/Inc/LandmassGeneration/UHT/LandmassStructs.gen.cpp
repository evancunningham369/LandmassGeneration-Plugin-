// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/LandmassStructs.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLandmassStructs() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector3f();
LANDMASSGENERATION_API UScriptStruct* Z_Construct_UScriptStruct_FTerrainChunkData();
LANDMASSGENERATION_API UScriptStruct* Z_Construct_UScriptStruct_FTriangle();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin ScriptStruct FTerrainChunkData
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_TerrainChunkData;
class UScriptStruct* FTerrainChunkData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TerrainChunkData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_TerrainChunkData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTerrainChunkData, (UObject*)Z_Construct_UPackage__Script_LandmassGeneration(), TEXT("TerrainChunkData"));
	}
	return Z_Registration_Info_UScriptStruct_TerrainChunkData.OuterSingleton;
}
template<> LANDMASSGENERATION_API UScriptStruct* StaticStruct<FTerrainChunkData>()
{
	return FTerrainChunkData::StaticStruct();
}
struct Z_Construct_UScriptStruct_FTerrainChunkData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "LandmassStructs.h" },
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTerrainChunkData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTerrainChunkData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
	nullptr,
	&NewStructOps,
	"TerrainChunkData",
	nullptr,
	0,
	sizeof(FTerrainChunkData),
	alignof(FTerrainChunkData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTerrainChunkData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTerrainChunkData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTerrainChunkData()
{
	if (!Z_Registration_Info_UScriptStruct_TerrainChunkData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_TerrainChunkData.InnerSingleton, Z_Construct_UScriptStruct_FTerrainChunkData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_TerrainChunkData.InnerSingleton;
}
// End ScriptStruct FTerrainChunkData

// Begin ScriptStruct FTriangle
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Triangle;
class UScriptStruct* FTriangle::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Triangle.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Triangle.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTriangle, (UObject*)Z_Construct_UPackage__Script_LandmassGeneration(), TEXT("Triangle"));
	}
	return Z_Registration_Info_UScriptStruct_Triangle.OuterSingleton;
}
template<> LANDMASSGENERATION_API UScriptStruct* StaticStruct<FTriangle>()
{
	return FTriangle::StaticStruct();
}
struct Z_Construct_UScriptStruct_FTriangle_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "LandmassStructs.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Vertex1_MetaData[] = {
		{ "ModuleRelativePath", "LandmassStructs.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Vertex2_MetaData[] = {
		{ "ModuleRelativePath", "LandmassStructs.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Vertex3_MetaData[] = {
		{ "ModuleRelativePath", "LandmassStructs.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Vertex1;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Vertex2;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Vertex3;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTriangle>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTriangle_Statics::NewProp_Vertex1 = { "Vertex1", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTriangle, Vertex1), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Vertex1_MetaData), NewProp_Vertex1_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTriangle_Statics::NewProp_Vertex2 = { "Vertex2", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTriangle, Vertex2), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Vertex2_MetaData), NewProp_Vertex2_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTriangle_Statics::NewProp_Vertex3 = { "Vertex3", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTriangle, Vertex3), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Vertex3_MetaData), NewProp_Vertex3_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTriangle_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTriangle_Statics::NewProp_Vertex1,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTriangle_Statics::NewProp_Vertex2,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTriangle_Statics::NewProp_Vertex3,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTriangle_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTriangle_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
	nullptr,
	&NewStructOps,
	"Triangle",
	Z_Construct_UScriptStruct_FTriangle_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTriangle_Statics::PropPointers),
	sizeof(FTriangle),
	alignof(FTriangle),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTriangle_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTriangle_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTriangle()
{
	if (!Z_Registration_Info_UScriptStruct_Triangle.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Triangle.InnerSingleton, Z_Construct_UScriptStruct_FTriangle_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_Triangle.InnerSingleton;
}
// End ScriptStruct FTriangle

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_LandmassStructs_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FTerrainChunkData::StaticStruct, Z_Construct_UScriptStruct_FTerrainChunkData_Statics::NewStructOps, TEXT("TerrainChunkData"), &Z_Registration_Info_UScriptStruct_TerrainChunkData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTerrainChunkData), 2815730896U) },
		{ FTriangle::StaticStruct, Z_Construct_UScriptStruct_FTriangle_Statics::NewStructOps, TEXT("Triangle"), &Z_Registration_Info_UScriptStruct_Triangle, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTriangle), 2262215305U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_LandmassStructs_h_2460359807(TEXT("/Script/LandmassGeneration"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_LandmassStructs_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_LandmassStructs_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
