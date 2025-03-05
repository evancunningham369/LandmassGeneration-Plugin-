// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Components/TerrainGeneratorComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTerrainGeneratorComponent() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FUintVector();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_ULandmassManagerSubsystem_NoRegister();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UTerrainChunkComponent_NoRegister();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UTerrainGeneratorComponent();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UTerrainGeneratorComponent_NoRegister();
LANDMASSGENERATION_API UScriptStruct* Z_Construct_UScriptStruct_FTerrainChunkInfo();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin ScriptStruct FTerrainChunkInfo
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_TerrainChunkInfo;
class UScriptStruct* FTerrainChunkInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TerrainChunkInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_TerrainChunkInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTerrainChunkInfo, (UObject*)Z_Construct_UPackage__Script_LandmassGeneration(), TEXT("TerrainChunkInfo"));
	}
	return Z_Registration_Info_UScriptStruct_TerrainChunkInfo.OuterSingleton;
}
template<> LANDMASSGENERATION_API UScriptStruct* StaticStruct<FTerrainChunkInfo>()
{
	return FTerrainChunkInfo::StaticStruct();
}
struct Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkCoords_MetaData[] = {
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ChunkCoords;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChunkComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTerrainChunkInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::NewProp_ChunkCoords = { "ChunkCoords", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTerrainChunkInfo, ChunkCoords), Z_Construct_UScriptStruct_FUintVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkCoords_MetaData), NewProp_ChunkCoords_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::NewProp_ChunkComponent = { "ChunkComponent", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTerrainChunkInfo, ChunkComponent), Z_Construct_UClass_UTerrainChunkComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkComponent_MetaData), NewProp_ChunkComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::NewProp_ChunkCoords,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::NewProp_ChunkComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
	nullptr,
	&NewStructOps,
	"TerrainChunkInfo",
	Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::PropPointers),
	sizeof(FTerrainChunkInfo),
	alignof(FTerrainChunkInfo),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTerrainChunkInfo()
{
	if (!Z_Registration_Info_UScriptStruct_TerrainChunkInfo.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_TerrainChunkInfo.InnerSingleton, Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_TerrainChunkInfo.InnerSingleton;
}
// End ScriptStruct FTerrainChunkInfo

// Begin Class UTerrainGeneratorComponent
void UTerrainGeneratorComponent::StaticRegisterNativesUTerrainGeneratorComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTerrainGeneratorComponent);
UClass* Z_Construct_UClass_UTerrainGeneratorComponent_NoRegister()
{
	return UTerrainGeneratorComponent::StaticClass();
}
struct Z_Construct_UClass_UTerrainGeneratorComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "Components/TerrainGeneratorComponent.h" },
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxTriangleCount_MetaData[] = {
		{ "Category", "Terrain Generation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The maximum number of triangles to generate */" },
#endif
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The maximum number of triangles to generate" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkSize_MetaData[] = {
		{ "Category", "Terrain Generation" },
		{ "ClampMax", "64" },
		{ "ClampMin", "8" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The size of each chunk in voxels */" },
#endif
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The size of each chunk in voxels" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkInfos_MetaData[] = {
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShaderSubsystem_MetaData[] = {
		{ "ModuleRelativePath", "Components/TerrainGeneratorComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxTriangleCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ChunkSize;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ChunkInfos_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ChunkInfos;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ShaderSubsystem;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTerrainGeneratorComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_MaxTriangleCount = { "MaxTriangleCount", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTerrainGeneratorComponent, MaxTriangleCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxTriangleCount_MetaData), NewProp_MaxTriangleCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ChunkSize = { "ChunkSize", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTerrainGeneratorComponent, ChunkSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkSize_MetaData), NewProp_ChunkSize_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ChunkInfos_Inner = { "ChunkInfos", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTerrainChunkInfo, METADATA_PARAMS(0, nullptr) }; // 1346416086
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ChunkInfos = { "ChunkInfos", nullptr, (EPropertyFlags)0x0040008000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTerrainGeneratorComponent, ChunkInfos), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkInfos_MetaData), NewProp_ChunkInfos_MetaData) }; // 1346416086
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ShaderSubsystem = { "ShaderSubsystem", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTerrainGeneratorComponent, ShaderSubsystem), Z_Construct_UClass_ULandmassManagerSubsystem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShaderSubsystem_MetaData), NewProp_ShaderSubsystem_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTerrainGeneratorComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_MaxTriangleCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ChunkSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ChunkInfos_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ChunkInfos,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTerrainGeneratorComponent_Statics::NewProp_ShaderSubsystem,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainGeneratorComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UTerrainGeneratorComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USceneComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainGeneratorComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTerrainGeneratorComponent_Statics::ClassParams = {
	&UTerrainGeneratorComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UTerrainGeneratorComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainGeneratorComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTerrainGeneratorComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UTerrainGeneratorComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTerrainGeneratorComponent()
{
	if (!Z_Registration_Info_UClass_UTerrainGeneratorComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTerrainGeneratorComponent.OuterSingleton, Z_Construct_UClass_UTerrainGeneratorComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTerrainGeneratorComponent.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<UTerrainGeneratorComponent>()
{
	return UTerrainGeneratorComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTerrainGeneratorComponent);
UTerrainGeneratorComponent::~UTerrainGeneratorComponent() {}
// End Class UTerrainGeneratorComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FTerrainChunkInfo::StaticStruct, Z_Construct_UScriptStruct_FTerrainChunkInfo_Statics::NewStructOps, TEXT("TerrainChunkInfo"), &Z_Registration_Info_UScriptStruct_TerrainChunkInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTerrainChunkInfo), 1346416086U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTerrainGeneratorComponent, UTerrainGeneratorComponent::StaticClass, TEXT("UTerrainGeneratorComponent"), &Z_Registration_Info_UClass_UTerrainGeneratorComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTerrainGeneratorComponent), 3380642125U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_3307122657(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_TerrainGeneratorComponent_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
