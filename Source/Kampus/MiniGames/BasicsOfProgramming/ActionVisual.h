// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Button.h"
#include "CodeBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/Action.h"
#include "ActionVisual.generated.h"

class UComboBoxString;
/**
 * 
 */
UCLASS()
class KAMPUS_API UActionVisual : public UCodeBaseWidget, public ICodeEntity, public IAction
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ActionSelector;

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteButton;

	TMap<FString, EActions> OptionToActions;
	
protected:

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	EActions GetAction(); virtual EActions GetAction_Implementation() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetAction(EActions Action); virtual void SetAction_Implementation(EActions Action) override;
	

	UFUNCTION()
	virtual void DeleteButtonOnClicked();
	UFUNCTION()
	virtual void  ActionSelectorOnChanged(FString SelectedOption, ESelectInfo::Type SelectionType);
};
