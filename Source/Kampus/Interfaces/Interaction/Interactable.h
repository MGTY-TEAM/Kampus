// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "Interactable.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(LogInteraction, Log, All);

// This class does not need to be modified.
UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class KAMPUS_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;
	bool bCanInteract;

	virtual void EndInteract() = 0;
};
