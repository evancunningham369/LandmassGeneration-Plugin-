// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Landmass/LandmassTypes.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LANDMASSGENERATION_LandmassTypes_generated_h
#error "LandmassTypes.generated.h already included, missing '#pragma once' in LandmassTypes.h"
#endif
#define LANDMASSGENERATION_LandmassTypes_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_donut_Documents_LandmassGenerationUnreal_LandmassGeneration_Source_LandmassGeneration_Landmass_LandmassTypes_h


#define FOREACH_ENUM_ELANDMASSTYPE(op) \
	op(ELandmassType::ELMT_BottomRight) \
	op(ELandmassType::ELMT_BottomLeft) \
	op(ELandmassType::ELMT_TopLeft) \
	op(ELandmassType::ELMT_TopRight) \
	op(ELandmassType::ELMT_Middle) \
	op(ELandmassType::ELMT_TopEdge) \
	op(ELandmassType::ELMT_LeftEdge) \
	op(ELandmassType::ELMT_RightEdge) \
	op(ELandmassType::ELMT_BottomEdge) \
	op(ELandmassType::ECS_MAX) 

enum class ELandmassType : uint8;
template<> struct TIsUEnumClass<ELandmassType> { enum { Value = true }; };
template<> LANDMASSGENERATION_API UEnum* StaticEnum<ELandmassType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
