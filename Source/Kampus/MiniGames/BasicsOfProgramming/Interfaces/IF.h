// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowControl.h"
#include "Interface.h"
#include "IF.generated.h"
UENUM()
enum class EConditions : uint8
{
	EFC_WALL_RIGHT = 0 UMETA(DisplayName = "Wall Right"),
	EFC_WALL_LEFT = 1 UMETA(DisplayName = "Wall Left"),
	EFC_WALL_FORWARD = 2 UMETA(DisplayName = "Wall Forward")
};

UINTERFACE()

class UIF : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KAMPUS_API IIF
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CalculateCondition();
	
	EConditions Condition;

	bool bHasElse;
};
