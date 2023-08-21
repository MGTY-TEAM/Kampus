// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "CodeEntity.h"
#include "Interface.h"
#include "FlowControl.generated.h"

UENUM(BlueprintType)
enum class EFlowControls : uint8
{
	EFC_IF = 0 UMETA(DisplayName = "Move"),
	EFC_IF_ELSE = 1 UMETA(DisplayName = "Rotate right"),
	EFC_While = 2 UMETA(DisplayName = "Rotate left")
};

UINTERFACE()

class UFlowControl : public UCodeEntity
{
	GENERATED_BODY()
};

/**
 * 
 */
class KAMPUS_API IFlowControl
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
