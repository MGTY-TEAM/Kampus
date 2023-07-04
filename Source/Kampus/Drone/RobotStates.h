// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/Blueprint.h"
#include "RobotStates.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERobotStates : uint8
{
  WEAP_Idle	UMETA(DisplayName = "Idle"),
  WEAP_PlayerInteract	UMETA(DisplayName = "PlayerInteract"),
  WEAP_Talk	UMETA(DisplayName = "Talk"),
  WEAP_Loading	UMETA(DisplayName = "Loading"),
};
