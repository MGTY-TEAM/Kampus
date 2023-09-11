// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ChatBox.h"

#include "Button.h"
#include "EditableTextBox.h"


bool UChatBox::Initialize()
{
	Super::Initialize();
	
	return true;
}

void UChatBox::NativeConstruct()
{
	SendMessage_TextBox->OnTextCommitted.AddDynamic(this, &UChatBox::OnTextBoxTextCommitted);

	SendMessage_Button->OnClicked.AddDynamic(this, &UChatBox::SendMessageButtonClicked);

	Super::NativeConstruct();
}

void UChatBox::SendMessageButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Button pressed"));
}

void UChatBox::OnTextBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enter Pressed"));
	}
}
