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
LANDMASSGENERATION_API UClass* Z_Construct_UClass_UGrassGeneratorComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_LandmassGeneration();
// End Cross Module References

// Begin Class ALandmass Function RegenerateGrass
struct Z_Construct_UFunction_ALandmass_RegenerateGrass_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Grass" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALandmass_RegenerateGrass_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALandmass, nullptr, "RegenerateGrass", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALandmass_RegenerateGrass_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALandmass_RegenerateGrass_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ALandmass_RegenerateGrass()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALandmass_RegenerateGrass_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ALandmass::execRegenerateGrass)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RegenerateGrass();
	P_NATIVE_END;
}
// End Class ALandmass Function RegenerateGrass

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
		{ "RegenerateGrass", &ALandmass::execRegenerateGrass },
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GrassGeneratorComponent_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsEdit_MetaData[] = {
		{ "Category", "Terrain Generation" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableGrass_MetaData[] = {
		{ "Category", "Grass" },
		{ "ModuleRelativePath", "Landmass/Landmass.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GrassGeneratorComponent;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxTriangles;
	static void NewProp_bEnableDebugVisualization_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableDebugVisualization;
	static void NewProp_bIsEdit_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsEdit;
	static void NewProp_bEnableGrass_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableGrass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ALandmass_RegenerateGrass, "RegenerateGrass" }, // 773465766
		{ &Z_Construct_UFunction_ALandmass_RegenerateTerrain, "RegenerateTerrain" }, // 2157241250
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALandmass>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_GrassGeneratorComponent = { "GrassGeneratorComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmass, GrassGeneratorComponent), Z_Construct_UClass_UGrassGeneratorComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GrassGeneratorComponent_MetaData), NewProp_GrassGeneratorComponent_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_MaxTriangles = { "MaxTriangles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALandmass, MaxTriangles), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxTriangles_MetaData), NewProp_MaxTriangles_MetaData) };
void Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableDebugVisualization_SetBit(void* Obj)
{
	((ALandmass*)Obj)->bEnableDebugVisualization = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableDebugVisualization = { "bEnableDebugVisualization", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALandmass), &Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableDebugVisualization_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableDebugVisualization_MetaData), NewProp_bEnableDebugVisualization_MetaData) };
void Z_Construct_UClass_ALandmass_Statics::NewProp_bIsEdit_SetBit(void* Obj)
{
	((ALandmass*)Obj)->bIsEdit = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_bIsEdit = { "bIsEdit", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALandmass), &Z_Construct_UClass_ALandmass_Statics::NewProp_bIsEdit_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsEdit_MetaData), NewProp_bIsEdit_MetaData) };
void Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableGrass_SetBit(void* Obj)
{
	((ALandmass*)Obj)->bEnableGrass = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableGrass = { "bEnableGrass", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALandmass), &Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableGrass_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableGrass_MetaData), NewProp_bEnableGrass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALandmass_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_GrassGeneratorComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_MaxTriangles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableDebugVisualization,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_bIsEdit,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALandmass_Statics::NewProp_bEnableGrass,
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
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALandmass, ALandmass::StaticClass, TEXT("ALandmass"), &Z_Registration_Info_UClass_ALandmass, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALandmass), 49297531U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_4186688862(TEXT("/Script/LandmassGeneration"),
	Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
