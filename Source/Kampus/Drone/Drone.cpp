// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"

#include "AudioMixerTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Core/BaseFirstPersonCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"


// Constructor. Called when an object of the class is created
ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true;  // Allows to update every tick
	Robot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Robot")); // Creates the Robot component
	Face = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face")); // Creates the Face component
	Face->SetupAttachment(Robot); // Attaches Face to Robot
}

// Function is called when interaction happens
void ADrone::Interact()
{
	ChangeState(ERobotStates::WEAP_PlayerInteract); // Changes the state to "PlayerInteract"
}

// Function is called when interaction ends
void ADrone::EndInteract()
{
	ChangeState(ERobotStates::WEAP_Idle); // Changes the state to "Idle"
}

// Changes the state of the object based on the passed parameter
void ADrone::ChangeState(ERobotStates State, float Duration)
{
	// Depending on the state, outputs the corresponding text to the log
	switch (State)
	{
	case ERobotStates::WEAP_Idle:
		UE_LOG(LogTemp, Warning, TEXT("Robot is idle."));
		break;

	case ERobotStates::WEAP_PlayerInteract:
		UE_LOG(LogTemp, Warning, TEXT("Robot is interacting with player."));
		CurrentState = ERobotStates::WEAP_PlayerInteract;
		break;

	case ERobotStates::WEAP_Talk:
		UE_LOG(LogTemp, Warning, TEXT("Robot is talking."));
		break;

	case ERobotStates::WEAP_Loading:
		UE_LOG(LogTemp, Warning, TEXT("Robot is loading."));
		break;
		
	}
}

// Called at the start of the game
void ADrone::BeginPlay()
{
	Super::BeginPlay(); // Calls the base BeginPlay function

	PlayerCharacter = Cast<ABaseFirstPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()); // Gets the player
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Calls the base Tick function

	if (CurrentState == ERobotStates::WEAP_PlayerInteract)
	{
		// If the state is "PlayerInteract", then the following code is executed
		// Makes the drone always look at the player

		FVector StartLocation = this->GetCapsuleComponent()->GetComponentLocation(); // Starting position of the drone
		FVector TargetLocation = PlayerCharacter->GetActorLocation(); // Player's position

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation); // Calculates the look-at vector from the drone to the player
	
		FRotator StartRotation = this->GetCapsuleComponent()->GetComponentRotation(); // Starting rotation of the drone
		FRotator EndRotation = LookAtRotation; // Final rotation - look at the player
		RotationSpeed = 1.0f; // Rotation speed

		// Calculates the interpolated rotation
		FRotator InterpolatedRotation = FMath::RInterpTo(StartRotation, EndRotation, DeltaTime, RotationSpeed);
		// Applies the interpolated rotation to the capsule component
		this->GetCapsuleComponent()->SetWorldRotation(InterpolatedRotation);
	}
}

// Sets up player input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); // Calls the base SetupPlayerInputComponent function
}