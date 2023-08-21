// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckBox.h"
#include "CodeBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/CodeEntity.h"
#include "Interfaces/FlowControl.h"
#include "Interfaces/IF.h"
#include "IfVisual.generated.h"

class UCodeListing;
class UButton;
class UComboBoxString;
/**
 * 
 */
UCLASS()
class KAMPUS_API UIfVisual : public UCodeBaseWidget, public ICodeEntity, public IIF
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ConditionSelector;
	
	UPROPERTY(meta = (BindWidget))
	UCodeListing* TrueCodeListing;
	
	UCodeListing* FalseCodeListing;

	UPROPERTY(meta = (BindWidget))
	UButton* RemoveButton;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* ElseCheckBox;
protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CalculateCondition(); virtual bool CalculateCondition_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveCall(UCodeBaseWidget* ChildWidget); virtual void RemoveCall_Implementation(UCodeBaseWidget* ChildWidget) override;
	
	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	virtual void ConditionSelectorOnChanged(FString SelectedOption, ESelectInfo::Type SelectionType);
	UFUNCTION()
	virtual void ElseCheckBoxOnChanged(bool State);
	UFUNCTION()
	virtual void RemoveButtonOnClicked();
private:
	TMap<FString, EConditions> OptionToConditions;
};


