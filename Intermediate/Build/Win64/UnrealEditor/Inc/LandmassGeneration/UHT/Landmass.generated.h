// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Landmass/Landmass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LANDMASSGENERATION_Landmass_generated_h
#error "Landmass.generated.h already included, missing '#pragma once' in Landmass.h"
#endif
#define LANDMASSGENERATION_Landmass_generated_h

#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execRegenerateGrass); \
	DECLARE_FUNCTION(execRegenerateTerrain);


#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALandmass(); \
	friend struct Z_Construct_UClass_ALandmass_Statics; \
public: \
	DECLARE_CLASS(ALandmass, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LandmassGeneration"), NO_API) \
	DECLARE_SERIALIZER(ALandmass)


#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ALandmass(ALandmass&&); \
	ALandmass(const ALandmass&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALandmass); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALandmass); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ALandmass) \
	NO_API virtual ~ALandmass();


#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_10_PROLOG
#define FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_13_INCLASS_NO_PURE_DECLS \
	FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LANDMASSGENERATION_API UClass* StaticClass<class ALandmass>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_Landmass_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
