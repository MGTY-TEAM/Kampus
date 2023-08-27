// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/CodeEntity.h"
#include "WhileVisual.generated.h"

class UButton;
class UCodeListing;
UCLASS()

class KAMPUS_API UWhileVisual : public UCodeBaseWidget, public ICodeEntity
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UButton* RemoveButton;

	UPROPERTY(meta=(BindWidget))
	UCodeListing* TrueCodeListing;

	
protected:
	
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	virtual void RemoveButtonOnClicked();
};
