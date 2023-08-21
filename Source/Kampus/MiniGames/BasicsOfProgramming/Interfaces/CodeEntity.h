// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "CodeEntity.generated.h"
class UCodeBaseWidget;
class UUserWidget;

// This class does not need to be modified.
UINTERFACE()
class UCodeEntity : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class KAMPUS_API ICodeEntity
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveCall(UCodeBaseWidget* ChildWidget);
	
	ICodeEntity* Parrent;
};

