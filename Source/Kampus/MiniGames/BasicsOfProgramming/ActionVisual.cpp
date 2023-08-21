// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionVisual.h"
#include "ComboBoxString.h"

void UActionVisual::NativeConstruct()
{
	Super::NativeConstruct();

	OptionToActions.Add("Move", EActions::EA_MOVE);
	OptionToActions.Add("RotateRight", EActions::EA_ROTATE_RIGHT);
	OptionToActions.Add("RotateLeft", EActions::EA_ROTATE_LEFT);


	for (TPair<FString, EActions> OptionToAction : OptionToActions)
	{
		ActionSelector->AddOption(OptionToAction.Key);
	}

	ActionSelector->SetSelectedOption(OptionToActions.begin().Key());

	ActionSelector->OnSelectionChanged.AddDynamic(this, &UActionVisual::ActionSelectorOnChanged);

	DeleteButton->OnClicked.AddDynamic(this, &UActionVisual::DeleteButtonOnClicked);
}

EActions UActionVisual::GetAction_Implementation()
{
	IAction::GetAction_Implementation();
	return Action;
}

void UActionVisual::SetAction_Implementation(EActions Action)
{
	IAction::SetAction_Implementation(Action);
	IAction::Action = Action;
}



void UActionVisual::DeleteButtonOnClicked()
{
	if (Parrent)
	{
		Parrent->RemoveCall_Implementation(this);
	}
}

void UActionVisual::ActionSelectorOnChanged(FString SelectedOption, ESelectInfo::Type SelectionType)
{ 
	EActions Action = OptionToActions[SelectedOption];
	this->Action = Action;
	
	if (true)
	{
		#if WITH_EDITOR
			UE_LOG(LogTemp, Warning, TEXT("Action selector value equals (%s) in (%s)"), *SelectedOption, *this->GetName());
		#endif
	}
	else
	{
		#if WITH_EDITOR
			UE_LOG(LogTemp, Warning, TEXT("Option (%s) is not finded in map"),*SelectedOption);
		#endif
	}
}
