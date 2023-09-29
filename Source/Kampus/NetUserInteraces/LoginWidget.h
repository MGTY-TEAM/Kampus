﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntryFormExecute.h"
#include "UserWidget.h"
#include "LoginWidget.generated.h"

class UEditableTextBox;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class KAMPUS_API ULoginWidget : public UUserWidget, public IEntryFormExecute
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* LoginText;
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* PasswordText;
	
	UPROPERTY(meta =(BindWidget))
	UTextBlock* ErrorText;
	
	UPROPERTY(meta =(BindWidget))
	UButton* LoginButton;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnLoginButtonClicked();

	FString GetStringValueFromEditableTextBox(UEditableTextBox* EditableTextBox) const;
	
};
