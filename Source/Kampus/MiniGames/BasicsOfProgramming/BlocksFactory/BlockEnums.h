// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockEnums.generated.h"

namespace BlockControls
{
	UENUM(BlueprintType)
	enum class EOperation : uint8
	{
		EOP_MOVE = 0 UMETA(DisplayName = "Move"),
		EOP_ROTATE_RIGHT = 1 UMETA(DisplayName = "RotateRight"),
		EOP_ROTATE_LEFT = 2 UMETA(DisplayName = "RotateLeft")
	};

	UENUM(BlueprintType)
	enum class EFlowControls : uint8
	{
		EOP_IF = 0 UMETA(DisplayName = "If"),
		EOP_WHILE = 1 UMETA(DisplayName = "While"),
		EOP_DO_N = 2 UMETA(DisplayName = "DoN")
	};

	UENUM(BlueprintType)
	enum class EConditions : uint8
	{
		EOP_WALL_FORWARD = 0 UMETA(DisplayName = "WallForward"),
		EOP_WALL_RIGHT = 1 UMETA(DisplayName = "WallRight"),
		EOP_WALL_LEFT = 2 UMETA(DisplayName = "WallLeft")
	};

}
