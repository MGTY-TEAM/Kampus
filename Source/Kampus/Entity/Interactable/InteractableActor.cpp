// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"


AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bCanInteract = true;
}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableActor::Interact()
{
	if (bCanInteract)
	{
		UE_LOG(LogInteraction, Log, TEXT("Interaction Succided"));
	}
	else
	{
		UE_LOG(LogInteraction, Error, TEXT("Interaction Faled"));
	}
}

void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
