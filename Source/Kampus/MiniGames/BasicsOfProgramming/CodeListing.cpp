// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeListing.h"

#include "VerticalBox.h"
#include "../../../../../../../../../Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/ucrt/complex.h"

TMap<ICodeEntity*, UCodeBaseWidget*> UCodeListing::GetCodeEntities()
{
	return CodeEntities;
}


void UCodeListing::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCodeListing::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCodeListing::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//Initialise ComboBox Values and Compare his with corresponding UI Class 
	OptionToEntityMap.Add(TPair<FString, TSubclassOf<UCodeBaseWidget>>("ACTION", ActionWidget));
	OptionToEntityMap.Add(TPair<FString, TSubclassOf<UCodeBaseWidget>>("IF", IfWidget));
	OptionToEntityMap.Add(TPair<FString, TSubclassOf<UCodeBaseWidget>>("WHILE", WhileWidget));

	//Fill ComboBox
	for (auto OptionsToEntity : OptionToEntityMap)
	{
		AddEntitySelector->AddOption(OptionsToEntity.Key);
	}

	AddEntitySelector->OnSelectionChanged.AddDynamic(this, &UCodeListing::AddSelectorOnChanged);
}

TArray<UCodeBaseWidget*> UCodeListing::GetEntities()
{
	TArray<UCodeBaseWidget*> Entities;
	for (auto CodeEntity : CodeEntities)
	{
		Entities.Add(CodeEntity.Value);
	}
	return Entities;
}


void UCodeListing::AddSelectorOnChanged(FString SelectedString, ESelectInfo::Type SelectionType)
{
	if (SelectedString != "")
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Add Selector: %s"), *SelectedString);
#endif

		UCodeBaseWidget* CurrentWidget = Cast<UCodeBaseWidget>(CreateWidget(this, OptionToEntityMap[SelectedString]));
		if (CurrentWidget)
		{
			VerticalCodeListing->AddChild(CurrentWidget);
			ICodeEntity* CurrentCodeEntity = Cast<ICodeEntity>(CurrentWidget);
			if (CurrentCodeEntity)
			{
				CodeEntities.Add(CurrentCodeEntity, CurrentWidget);
				CurrentCodeEntity->Parrent = this;
			}
		}
		AddEntitySelector->ClearSelection();
	}
}

void UCodeListing::RemoveCall_Implementation(UCodeBaseWidget* ChildEntity)
{
	if (ChildEntity)
	{
		for (auto EntityToWidget : CodeEntities)
		{
			if (EntityToWidget.Value == ChildEntity)
			{
#if WITH_EDITOR
				UE_LOG(LogTemp, Warning, TEXT("Remove code entity (%s) from map"), *ChildEntity->GetName())
#endif
				CodeEntities.Remove(EntityToWidget.Key);
				ChildEntity->RemoveFromParent();
				break;
			}
		}
	}
}
