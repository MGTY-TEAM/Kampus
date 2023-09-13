// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ChatBox.h"

#include "Button.h"
#include "Chat_Message.h"
#include "EditableTextBox.h"
#include "ScrollBox.h"
#include "TextBlock.h"


bool UChatBox::Initialize()
{
	Super::Initialize();
	
	
	return true;
}

void UChatBox::NativeConstruct()
{
	//SendMessage_TextBox->OnTextCommitted.AddDynamic(this, &UChatBox::OnTextBoxTextCommitted);
	

	SendMessage_Button->OnClicked.AddDynamic(this, &UChatBox::SendMessageButtonClicked);

	Super::NativeConstruct();
}

void UChatBox::SendMessageButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Button pressed"));
	SendMessage(SendMessage_TextBox->GetText());
}

/*void UChatBox::OnTextBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enter Pressed"));
	}
}*/

void UChatBox::SendMessage(FText Text)
{
	UChat_Message* WidgetInstance = CreateWidget<UChat_Message>(GetWorld()->GetFirstPlayerController(), BlueprintWidgetClass);
	
	if (WidgetInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("SendMessage"));
		WidgetInstance->AddToViewport();
		Chat_ScrollBox->AddChild(WidgetInstance);

		
		WidgetInstance->Message->SetText(Text);
		
		SendMessage_TextBox->SetText(FText::GetEmpty());
		
		
	}
	
	
}
