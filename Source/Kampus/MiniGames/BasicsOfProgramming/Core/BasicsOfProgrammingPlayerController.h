// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicsOfProgrammingPlayerController.generated.h"
class ABlockBase;
UCLASS()
class KAMPUS_API ABasicsOfProgrammingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABasicsOfProgrammingPlayerController();
	bool bLeftMouseButtonPressed;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void MouseLook();
	virtual void SetupInputComponent() override;

	virtual void LeftMouseButtonPressed();
	virtual void LeftMouseButtonReleased();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	 ABlockBase* CurrentBlockOnFocuse{nullptr};
};
