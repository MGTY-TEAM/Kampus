// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"

#include "AudioMixerTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Core/BaseFirstPersonCharacter.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "UserInterface/ChatBox.h"


// Constructor. Called when an object of the class is created
ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true; // Allows to update every tick
	Robot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Robot")); // Creates the Robot component
	Face = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face")); // Creates the Face component
	Face->SetupAttachment(Robot); // Attaches Face to Robot

	
}

void ADrone::TeleportToLocation(int index)
{
	TeleportationPlace = Cast<ATeleportationPlane>(TeleportationPlaces[index]);
	if (TeleportationPlace)
	{
		SetActorLocation(TeleportationPlace->RobotPlane->GetComponentLocation());
	}
}

// Function is called when interaction happens
void ADrone::Interact()
{
	ChangeState(ERobotStates::Drone_PlayerInteract);// Changes the state to "PlayerInteract"
	ChatWidget = CreateWidget<UChatBox>(GetWorld()->GetFirstPlayerController(), BlueprintChatClass);
	if (!ChatWidget->IsInViewport())
	{
		ChatWidget->AddToPlayerScreen();
		UE_LOG(LogTemp, Warning, TEXT("AddToScreen"));
	}
	ChatWidget->SetVisibility(ESlateVisibility::Visible);
}

// Function is called when interaction ends
void ADrone::EndInteract()
{
	ChangeState(ERobotStates::Drone_Idle); // Changes the state to "Idle"
	UE_LOG(LogTemp, Warning, TEXT("EndInteract"));
	GetWorldTimerManager().ClearTimer(RotateToPlayer_Timer);
	ChatWidget->SetVisibility(ESlateVisibility::Hidden);
}

// Changes the state of the object based on the passed parameter
void ADrone::ChangeState(ERobotStates State, float Duration)
{
	CurrentState = State;
	switch (CurrentState)
	{
	case ERobotStates::Drone_Idle:
		IdleAnim();
		break;

	case ERobotStates::Drone_PlayerInteract:
		RotateToPlayer();
		break;

	case ERobotStates::Drone_Talk:
		break;

	case ERobotStates::Drone_Loading:
		break;

	case ERobotStates::Drone_Follow:
		break;
	}
}

void ADrone::IdleAnim()
{
	GetWorld()->GetTimerManager().SetTimer(IdleAnim_Timer, this, &ADrone::IdleAnim, 0.01f, true);
	float TimeSeconds = GetWorld()->GetTimeSeconds();
	float Movement = (sin(TimeSeconds * Frecuency1) * Amplitude1) + Robot->GetComponentLocation().Z;
	Robot->SetWorldLocation(FVector(Robot->GetComponentLocation().X, Robot->GetComponentLocation().Y, Movement));
}

void ADrone::RotateToPlayer()
{
	GetWorld()->GetTimerManager().SetTimer(RotateToPlayer_Timer, this, &ADrone::RotateToPlayer, 0.01f, true);
	FVector StartLocation = GetCapsuleComponent()->GetComponentLocation(); // Starting position of the drone
	FVector TargetLocation = PlayerCharacter->GetActorLocation(); // Player's position
	
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation); // Calculates the look-at vector from the drone to the player
	FRotator StartRotation = GetCapsuleComponent()->GetComponentRotation(); // Starting rotation of the drone
	FRotator EndRotation = LookAtRotation; // Final rotation - look at the player
	
	// Calculates the interpolated rotation
	FRotator InterpolatedRotation = FMath::RInterpTo(StartRotation, EndRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
	// Applies the interpolated rotation to the capsule component
	GetCapsuleComponent()->SetWorldRotation(InterpolatedRotation);
}


// Called at the start of the game
void ADrone::BeginPlay()
{
	Super::BeginPlay(); // Calls the base BeginPlay function

	ChangeState(ERobotStates::Drone_Idle, 0.0f);
	PlayerCharacter = Cast<ABaseFirstPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (ChatWidget)
	{
		ChatWidget->TeleportationEvent.AddDynamic(this, &ADrone::TeleportToLocation);
	}
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Calls the base Tick function
	
	
}

// Sets up player input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); // Calls the base SetupPlayerInputComponent function
}