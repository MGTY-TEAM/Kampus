// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneGuide.h"

#include "UserWidget.h"


void ADroneGuide::BeginPlay()
{
	Super::BeginPlay();
	ChangeState(EDroneGuide::Drone_Idle);
	ChatWidget = CreateWidget<UChatBox>(GetWorld()->GetFirstPlayerController(), BlueprintChatClass);
}

void ADroneGuide::Interact()
{
	Super::Interact();
	ChangeState(EDroneGuide::Drone_PlayerInteract);
	OpenChat();
}

void ADroneGuide::EndInteract()
{
	Super::EndInteract();
	ChangeState(EDroneGuide::Drone_Idle);
	CloseChat();
}

void ADroneGuide::ChangeState(EDroneGuide State, float Duration)
{
	switch (State)
	{
	case EDroneGuide::Drone_Idle:
		StartIdleAnim();
		StopRotateToPlayerAnim();
		break;
	case EDroneGuide::Drone_PlayerInteract:
		StartRotateToPlayerAnim();
		break;
	}
	
}

void ADroneGuide::StartIdleAnim()
{
	Super::StartIdleAnim();
}

void ADroneGuide::StopIdleAnim()
{
	Super::StopIdleAnim();
}

void ADroneGuide::StartRotateToPlayerAnim()
{
	Super::StartRotateToPlayerAnim();
}

void ADroneGuide::StopRotateToPlayerAnim()
{
	Super::StopRotateToPlayerAnim();
}

void ADroneGuide::OpenChat()
{
	if (!ChatWidget->IsInViewport())
	{
		ChatWidget->AddToPlayerScreen();
		UE_LOG(LogTemp, Warning, TEXT("AddToScreen"));
	}
	ChatWidget->SetVisibility(ESlateVisibility::Visible);
}

void ADroneGuide::CloseChat()
{
	ChatWidget->SetVisibility(ESlateVisibility::Hidden);
}

