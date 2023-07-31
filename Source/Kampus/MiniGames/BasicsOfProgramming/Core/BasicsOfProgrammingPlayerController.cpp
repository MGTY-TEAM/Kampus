// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicsOfProgrammingPlayerController.h"

#include "Engine/Engine.h"
#include "MiniGames/BasicsOfProgramming/BlocksFactory/BlockBase.h"


// Sets default values
ABasicsOfProgrammingPlayerController::ABasicsOfProgrammingPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}

// Called when the game starts or when spawned
void ABasicsOfProgrammingPlayerController::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ABasicsOfProgrammingPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MouseLook();
}


void ABasicsOfProgrammingPlayerController::MouseLook()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	if (HitResult.IsValidBlockingHit())

		if (bLeftMouseButtonPressed)
		{
			ABlockBase* Block = Cast<ABlockBase>(HitResult.Actor);
			if (Block)
			{
				CurrentBlockOnFocuse = Block;
				GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Black, TEXT("Debug"));
			}
			if (CurrentBlockOnFocuse)
			{
				CurrentBlockOnFocuse->OnDrag(HitResult.Location);
			}
		}
}

void ABasicsOfProgrammingPlayerController::LeftMouseButtonPressed()
{
	bLeftMouseButtonPressed = true;
}

void ABasicsOfProgrammingPlayerController::LeftMouseButtonReleased()
{
	bLeftMouseButtonPressed = false;
}

void ABasicsOfProgrammingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("UI_Interaction", IE_Pressed, this,
	                           &ABasicsOfProgrammingPlayerController::LeftMouseButtonPressed);
	InputComponent->BindAction("UI_Interaction", IE_Released, this,
	                           &ABasicsOfProgrammingPlayerController::LeftMouseButtonReleased);
}
