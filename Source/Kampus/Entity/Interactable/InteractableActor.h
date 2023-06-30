// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interaction/Interactable.h"
#include "InteractableActor.generated.h"

UCLASS()
class KAMPUS_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AInteractableActor();

protected:
	virtual void BeginPlay() override;

	virtual void Interact() override;

public:
	virtual void Tick(float DeltaTime) override;
};
