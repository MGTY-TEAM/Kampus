// Fill out your copyright notice in the Description page of Project Settings.


#include "IfVisual.h"

#include "Button.h"
#include "ComboBoxString.h"

bool UIfVisual::CalculateCondition_Implementation()
{
	if (Condition == EConditions::EFC_WALL_FORWARD)
	{
		return true;
	}
	return false;
	
}

void UIfVisual::RemoveCall_Implementation(UCodeBaseWidget* ChildWidget)
{
	ICodeEntity::RemoveCall_Implementation(ChildWidget);
}

void UIfVisual::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	OptionToConditions.Add("Wall Forward",EConditions::EFC_WALL_FORWARD);
	OptionToConditions.Add("Wall Right", EConditions::EFC_WALL_RIGHT);
	OptionToConditions.Add("Wall Left", EConditions:: EFC_WALL_LEFT);

	for (auto OptionToCondition : OptionToConditions)
	{
		ConditionSelector->AddOption(OptionToCondition.Key);
	}
	
	ConditionSelector->SetSelectedIndex(0);
	
	ConditionSelector->OnSelectionChanged.AddDynamic(this, &UIfVisual::ConditionSelectorOnChanged);

	ElseCheckBox->OnCheckStateChanged.AddDynamic(this, &UIfVisual::ElseCheckBoxOnChanged);

	RemoveButton->OnClicked.AddDynamic(this, &UIfVisual::RemoveButtonOnClicked);
}

void UIfVisual::ConditionSelectorOnChanged(FString SelectedOption, ESelectInfo::Type SelectionType)
{
	if (SelectedOption != "")
	{
		Condition = OptionToConditions[SelectedOption];
	}
}

void UIfVisual::RemoveButtonOnClicked()
{
	if (Parrent)
	{
		Parrent->RemoveCall_Implementation(this);
	}
}

void UIfVisual::ElseCheckBoxOnChanged(bool State)
{
	
}
