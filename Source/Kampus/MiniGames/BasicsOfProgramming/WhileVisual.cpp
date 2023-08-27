// Fill out your copyright notice in the Description page of Project Settings.


#include "WhileVisual.h"

#include "Button.h"


void UWhileVisual::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RemoveButton->OnClicked.AddDynamic(this, &UWhileVisual::RemoveButtonOnClicked);
}

void UWhileVisual::RemoveButtonOnClicked()
{
	if (Parrent)
	{
		Parrent->RemoveCall_Implementation(this);
	}
	RemoveFromParent();
}
