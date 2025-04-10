// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LandmassGeneration/Components/GrassGeneratorComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGrassGeneratorComponent() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UGrassGeneratorComponent();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UGrassGeneratorComponent_NoRegister();
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UTerrainGeneratorComponent_NoRegister();
LANDMASSGENERATION_API UScriptStruct* Z_Construct_UScriptStruct_FGrassType();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin ScriptStruct FGrassType
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GrassType;
class UScriptStruct* FGrassType::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GrassType.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GrassType.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGrassType, (UObject*)Z_Construct_UPackage__Script_LandmassGeneration(), TEXT("GrassType"));
	}
	return Z_Registration_Info_UScriptStruct_GrassType.OuterSingleton;
}
template<> LANDMASSGENERATION_API UScriptStruct* StaticStruct<FGrassType>()
{
	return FGrassType::StaticStruct();
}
struct Z_Construct_UScriptStruct_FGrassType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Structure to define a type of grass\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Structure to define a type of grass" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GrassMesh_MetaData[] = {
		{ "Category", "Grass" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The static mesh to use for this grass type\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The static mesh to use for this grass type" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Density_MetaData[] = {
		{ "Category", "Grass" },
		{ "ClampMax", "1000.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// How dense this grass type should be (instances per square meter)\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How dense this grass type should be (instances per square meter)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinScale_MetaData[] = {
		{ "Category", "Grass" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Minimum and maximum scale variation\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum and maximum scale variation" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxScale_MetaData[] = {
		{ "Category", "Grass" },
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxSlope_MetaData[] = {
		{ "Category", "Grass" },
		{ "ClampMax", "90.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Maximum slope angle where this grass can grow (in degrees)\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum slope angle where this grass can grow (in degrees)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRandomRotation_MetaData[] = {
		{ "Category", "Grass" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Allow random rotation on Z axis\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Allow random rotation on Z axis" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CullDistance_MetaData[] = {
		{ "Category", "Grass" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Distance to stop rendering this grass type\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance to stop rendering this grass type" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GrassMaterial_MetaData[] = {
		{ "Category", "Grass" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Material to use for the grass\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material to use for the grass" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GrassMesh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Density;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MinScale;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MaxScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxSlope;
	static void NewProp_bRandomRotation_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRandomRotation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CullDistance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GrassMaterial;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGrassType>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_GrassMesh = { "GrassMesh", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGrassType, GrassMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GrassMesh_MetaData), NewProp_GrassMesh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_Density = { "Density", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGrassType, Density), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Density_MetaData), NewProp_Density_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_MinScale = { "MinScale", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGrassType, MinScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinScale_MetaData), NewProp_MinScale_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_MaxScale = { "MaxScale", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGrassType, MaxScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxScale_MetaData), NewProp_MaxScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_MaxSlope = { "MaxSlope", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGrassType, MaxSlope), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxSlope_MetaData), NewProp_MaxSlope_MetaData) };
void Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_bRandomRotation_SetBit(void* Obj)
{
	((FGrassType*)Obj)->bRandomRotation = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_bRandomRotation = { "bRandomRotation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FGrassType), &Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_bRandomRotation_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRandomRotation_MetaData), NewProp_bRandomRotation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_CullDistance = { "CullDistance", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGrassType, CullDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CullDistance_MetaData), NewProp_CullDistance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_GrassMaterial = { "GrassMaterial", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGrassType, GrassMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GrassMaterial_MetaData), NewProp_GrassMaterial_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGrassType_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_GrassMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_Density,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_MinScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_MaxScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_MaxSlope,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_bRandomRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_CullDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGrassType_Statics::NewProp_GrassMaterial,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGrassType_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGrassType_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
	nullptr,
	&NewStructOps,
	"GrassType",
	Z_Construct_UScriptStruct_FGrassType_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGrassType_Statics::PropPointers),
	sizeof(FGrassType),
	alignof(FGrassType),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGrassType_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGrassType_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGrassType()
{
	if (!Z_Registration_Info_UScriptStruct_GrassType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GrassType.InnerSingleton, Z_Construct_UScriptStruct_FGrassType_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_GrassType.InnerSingleton;
}
// End ScriptStruct FGrassType

// Begin Class UGrassGeneratorComponent Function GenerateGrass
struct Z_Construct_UFunction_UGrassGeneratorComponent_GenerateGrass_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Grass Generation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Generate grass using compute shaders\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Generate grass using compute shaders" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGrassGeneratorComponent_GenerateGrass_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGrassGeneratorComponent, nullptr, "GenerateGrass", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGrassGeneratorComponent_GenerateGrass_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGrassGeneratorComponent_GenerateGrass_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGrassGeneratorComponent_GenerateGrass()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGrassGeneratorComponent_GenerateGrass_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGrassGeneratorComponent::execGenerateGrass)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->GenerateGrass();
	P_NATIVE_END;
}
// End Class UGrassGeneratorComponent Function GenerateGrass

// Begin Class UGrassGeneratorComponent
void UGrassGeneratorComponent::StaticRegisterNativesUGrassGeneratorComponent()
{
	UClass* Class = UGrassGeneratorComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GenerateGrass", &UGrassGeneratorComponent::execGenerateGrass },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGrassGeneratorComponent);
UClass* Z_Construct_UClass_UGrassGeneratorComponent_NoRegister()
{
	return UGrassGeneratorComponent::StaticClass();
}
struct Z_Construct_UClass_UGrassGeneratorComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "LandmassGeneration" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Component responsible for generating and managing grass using GPU compute\n */" },
#endif
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "Components/GrassGeneratorComponent.h" },
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Component responsible for generating and managing grass using GPU compute" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GrassTypes_MetaData[] = {
		{ "Category", "Grass Generation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Different types of grass to generate\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Different types of grass to generate" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CellSize_MetaData[] = {
		{ "Category", "Grass Generation" },
		{ "ClampMax", "1000.0" },
		{ "ClampMin", "10.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Cell size for grass grid (in unreal units)\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cell size for grass grid (in unreal units)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxGrassInstances_MetaData[] = {
		{ "Category", "Grass Generation" },
		{ "ClampMax", "10000000" },
		{ "ClampMin", "1000" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Maximum number of grass instances (per type)\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum number of grass instances (per type)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUpdateWithTerrain_MetaData[] = {
		{ "Category", "Grass Generation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Whether to update grass in real-time when the terrain changes\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to update grass in real-time when the terrain changes" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FadeStartDistance_MetaData[] = {
		{ "Category", "Grass Generation" },
		{ "ClampMin", "100.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Distance from camera where grass begins to fade\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance from camera where grass begins to fade" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FadeEndDistance_MetaData[] = {
		{ "Category", "Grass Generation" },
		{ "ClampMin", "100.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Distance from camera where grass is fully culled\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance from camera where grass is fully culled" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DensityMultiplier_MetaData[] = {
		{ "Category", "Grass Generation" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Density multiplier for grass (can be adjusted at runtime)\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Density multiplier for grass (can be adjusted at runtime)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WindStrength_MetaData[] = {
		{ "Category", "Grass Generation" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Wind strength for grass animation\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Wind strength for grass animation" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RandomSeed_MetaData[] = {
		{ "Category", "Grass Generation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Seed for random number generation\n" },
#endif
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Seed for random number generation" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TerrainGenerator_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Cached terrain generator reference\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Components/GrassGeneratorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cached terrain generator reference" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_GrassTypes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_GrassTypes;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CellSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxGrassInstances;
	static void NewProp_bUpdateWithTerrain_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUpdateWithTerrain;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FadeStartDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FadeEndDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DensityMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WindStrength;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RandomSeed;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TerrainGenerator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGrassGeneratorComponent_GenerateGrass, "GenerateGrass" }, // 2054657774
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGrassGeneratorComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_GrassTypes_Inner = { "GrassTypes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGrassType, METADATA_PARAMS(0, nullptr) }; // 3286411869
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_GrassTypes = { "GrassTypes", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrassGeneratorComponent, GrassTypes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GrassTypes_MetaData), NewProp_GrassTypes_MetaData) }; // 3286411869
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_CellSize = { "CellSize", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrassGeneratorComponent, CellSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CellSize_MetaData), NewProp_CellSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_MaxGrassInstances = { "MaxGrassInstances", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrassGeneratorComponent, MaxGrassInstances), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxGrassInstances_MetaData), NewProp_MaxGrassInstances_MetaData) };
void Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_bUpdateWithTerrain_SetBit(void* Obj)
{
	((UGrassGeneratorComponent*)Obj)->bUpdateWithTerrain = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_bUpdateWithTerrain = { "bUpdateWithTerrain", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGrassGeneratorComponent), &Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_bUpdateWithTerrain_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUpdateWithTerrain_MetaData), NewProp_bUpdateWithTerrain_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_FadeStartDistance = { "FadeStartDistance", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrassGeneratorComponent, FadeStartDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FadeStartDistance_MetaData), NewProp_FadeStartDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_FadeEndDistance = { "FadeEndDistance", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrassGeneratorComponent, FadeEndDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FadeEndDistance_MetaData), NewProp_FadeEndDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_DensityMultiplier = { "DensityMultiplier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrassGeneratorComponent, DensityMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DensityMultiplier_MetaData), NewProp_DensityMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_WindStrength = { "WindStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrassGeneratorComponent, WindStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WindStrength_MetaData), NewProp_WindStrength_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_RandomSeed = { "RandomSeed", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrassGeneratorComponent, RandomSeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RandomSeed_MetaData), NewProp_RandomSeed_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_TerrainGenerator = { "TerrainGenerator", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrassGeneratorComponent, TerrainGenerator), Z_Construct_UClass_UTerrainGeneratorComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TerrainGenerator_MetaData), NewProp_TerrainGenerator_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGrassGeneratorComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_GrassTypes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_GrassTypes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_CellSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_MaxGrassInstances,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_bUpdateWithTerrain,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_FadeStartDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_FadeEndDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_DensityMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_WindStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_RandomSeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrassGeneratorComponent_Statics::NewProp_TerrainGenerator,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGrassGeneratorComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGrassGeneratorComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USceneComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_LandmassGeneration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGrassGeneratorComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGrassGeneratorComponent_Statics::ClassParams = {
	&UGrassGeneratorComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGrassGeneratorComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGrassGeneratorComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrassGeneratorComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UGrassGeneratorComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGrassGeneratorComponent()
{
	if (!Z_Registration_Info_UClass_UGrassGeneratorComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGrassGeneratorComponent.OuterSingleton, Z_Construct_UClass_UGrassGeneratorComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGrassGeneratorComponent.OuterSingleton;
}
template<> LANDMASSGENERATION_API UClass* StaticClass<UGrassGeneratorComponent>()
{
	return UGrassGeneratorComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGrassGeneratorComponent);
UGrassGeneratorComponent::~UGrassGeneratorComponent() {}
// End Class UGrassGeneratorComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FGrassType::StaticStruct, Z_Construct_UScriptStruct_FGrassType_Statics::NewStructOps, TEXT("GrassType"), &Z_Registration_Info_UScriptStruct_GrassType, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGrassType), 3286411869U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGrassGeneratorComponent, UGrassGeneratorComponent::StaticClass, TEXT("UGrassGeneratorComponent"), &Z_Registration_Info_UClass_UGrassGeneratorComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGrassGeneratorComponent), 3814124782U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_1326731515(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
