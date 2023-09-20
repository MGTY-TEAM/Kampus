// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ChatBox.h"

#include "Button.h"
#include "Chat_Message.h"
#include "EditableTextBox.h"
#include "ScrollBox.h"
#include "TextBlock.h"

#include "Requests/HTTPRequestsLib.h"


bool UChatBox::Initialize()
{
	Super::Initialize();

	Drone = Cast<ADrone>(UGameplayStatics::GetActorOfClass(GetWorld(), ADrone::StaticClass()));
	
		UHTTPRequestsLib::AIMyLogicGetRequest([=](const FString& Response)
		{
			SendMessage(FText::FromString(Response), FText::FromString("AI"));
			UE_LOG(LogTemp, Warning, TEXT("SetRequest"));
		}, "/start", Drone->BotURL);
	
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
	
	FString StringRequest = SendMessage_TextBox->GetText().ToString();
	
		UHTTPRequestsLib::AIMyLogicGetRequest([=](const FString& Response)
	{
			BotResponse(Response);//кал!!!
	}, StringRequest, Drone->BotURL);
	SendMessage(SendMessage_TextBox->GetText(), FText::FromString("User"));
}

/*void UChatBox::OnTextBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enter Pressed"));
	}
}*/

void UChatBox::SendMessage(FText Message, FText Sender)
{
	UChat_Message* WidgetInstance = CreateWidget<UChat_Message>(GetWorld()->GetFirstPlayerController(), BlueprintWidgetClass);
	
	if (WidgetInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("SendMessage"));
		WidgetInstance->AddToViewport();
		Chat_ScrollBox->AddChild(WidgetInstance);
		WidgetInstance->Message->SetText(Message);
		SendMessage_TextBox->SetText(FText::GetEmpty());
	}
}

void UChatBox::BotResponse(const FString& Result)
{
	UE_LOG(LogRequests, Log, TEXT("GET Request Result: %s"), *Result);
	SendMessage(FText::FromString(Result), FText::FromString("AI"));
	Chat_ScrollBox->ScrollToEnd();

	if (bCanRobotMoveToLocation)
	{
		for (int i = 0; i < Drone->KeyWordsPlaces.Num(); i++)
		{
			if (Result.Find(Drone->KeyWordsPlaces[i],ESearchCase::CaseSensitive) != INDEX_NONE)
			{
				UE_LOG(LogRequests, Error, TEXT("GET Request Result: %s"), *Drone->KeyWordsPlaces[i])
				TeleportationEvent.Broadcast(i);
				bCanRobotMoveToLocation = false;
			}
		}
	}
	
	for (int i = 0; i < Drone->KeyWordsForTeleportation.Num(); i++)
	{
		if (Result.Find(Drone->KeyWordsForTeleportation[i],ESearchCase::CaseSensitive) != INDEX_NONE)
		{
			UE_LOG(LogRequests, Error, TEXT("GET Request Result: %s"), *Drone->KeyWordsForTeleportation[i]);
			bCanRobotMoveToLocation = true;
		}
	}
}

