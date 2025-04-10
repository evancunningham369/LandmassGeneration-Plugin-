// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Components/GrassGeneratorComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LANDMASSGENERATION_GrassGeneratorComponent_generated_h
#error "GrassGeneratorComponent.generated.h already included, missing '#pragma once' in GrassGeneratorComponent.h"
#endif
#define LANDMASSGENERATION_GrassGeneratorComponent_generated_h

#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_15_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FGrassType_Statics; \
	LANDMASSGENERATION_API static class UScriptStruct* StaticStruct();


template<> LANDMASSGENERATION_API UScriptStruct* StaticStruct<struct FGrassType>();

#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGenerateGrass);


#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_59_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGrassGeneratorComponent(); \
	friend struct Z_Construct_UClass_UGrassGeneratorComponent_Statics; \
public: \
	DECLARE_CLASS(UGrassGeneratorComponent, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LandmassGeneration"), NO_API) \
	DECLARE_SERIALIZER(UGrassGeneratorComponent)


#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_59_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UGrassGeneratorComponent(UGrassGeneratorComponent&&); \
	UGrassGeneratorComponent(const UGrassGeneratorComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGrassGeneratorComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGrassGeneratorComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGrassGeneratorComponent) \
	NO_API virtual ~UGrassGeneratorComponent();


#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_56_PROLOG
#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_59_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_59_INCLASS_NO_PURE_DECLS \
	FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h_59_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LANDMASSGENERATION_API UClass* StaticClass<class UGrassGeneratorComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Components_GrassGeneratorComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
