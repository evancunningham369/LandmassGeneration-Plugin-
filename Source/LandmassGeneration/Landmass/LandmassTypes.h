#pragma once

UENUM(BlueprintType)
enum class ELandmassType : uint8
{
	ELMT_BottomRight UMETA(DisplayName = "Bottom Right Corner"),
	ELMT_BottomLeft UMETA(DisplayName = "Bottom Left Corner"),
	ELMT_TopLeft UMETA(DisplayName = "Top Left Corner"),
	ELMT_TopRight UMETA(DisplayName = "Top Right Corner"),

	ELMT_Middle UMETA(DisplayName = "Middle"),

	ELMT_TopEdge UMETA(DisplayName = "Top Edge"),
	ELMT_LeftEdge UMETA(DisplayName = "Left Edge"),
	ELMT_RightEdge UMETA(DisplayName = "Right Edge"),
	ELMT_BottomEdge UMETA(DisplayName = "Bottom Edge"),

	ECS_MAX UMETA(DisplayName = "DefaultMAX")

};