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
  Drone_Idle	UMETA(DisplayName = "Idle"),
  Drone_PlayerInteract	UMETA(DisplayName = "PlayerInteract"),
  Drone_Talk	UMETA(DisplayName = "Talk"),
  Drone_Loading	UMETA(DisplayName = "Loading"),
	Drone_Follow UMETA(Displayname = "PlayerFollow"),
};
