// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeEntity.h"
#include "Action.generated.h"

// This class does not need to be modified.

UENUM(BlueprintType)
enum class EActions : uint8
{
	EA_MOVE = 0 UMETA(DisplayName = "Move"),
	EA_ROTATE_RIGHT = 1 UMETA(DisplayName = "Rotate right"),
	EA_ROTATE_LEFT = 2 UMETA(DisplayName = "Rotate left")
};

UINTERFACE()
class UAction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KAMPUS_API IAction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	EActions Action;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EActions GetAction();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetAction(EActions Action);
	
	
	
};
