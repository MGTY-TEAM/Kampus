// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"

#include "AudioMixerTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Core/BaseFirstPersonCharacter.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
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
	ChangeState(ERobotStates::Drone_PlayerInteract); // Changes the state to "PlayerInteract"
}

// Function is called when interaction ends
void ADrone::EndInteract()
{
	ChangeState(ERobotStates::Drone_Idle); // Changes the state to "Idle"
	UE_LOG(LogTemp, Warning, TEXT("EndInteract"));
	GetWorldTimerManager().ClearTimer(RotateToPlayer_Timer);
}

// Changes the state of the object based on the passed parameter
void ADrone::ChangeState(ERobotStates State, float Duration)
{
	CurrentState = State;
	// Depending on the state, outputs the corresponding text to the log
}

void ADrone::IdleAnim()
{
	GetWorld()->GetTimerManager().SetTimer(IdleAnim_Timer, this, &ADrone::IdleAnim, 0.01f, true);
	float TimeSeconds = GetWorld()->GetTimeSeconds();
	float Movement = (sin(TimeSeconds * Frecuency1) * Amplitude1) + Robot->GetComponentLocation().Z;
	Robot->SetWorldLocation(FVector(Robot->GetComponentLocation().X, Robot->GetComponentLocation().Y, Movement));
	UE_LOG(LogTemp, Warning, TEXT("Idle"));
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
	PlayerCharacter = Cast<ABaseFirstPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()); // Gets the player
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Calls the base Tick function
	
	switch (CurrentState)
	{
	case ERobotStates::Drone_Idle:
		//UE_LOG(LogTemp, Warning, TEXT("Robot is idle.")); 
		IdleAnim();
		break;

	case ERobotStates::Drone_PlayerInteract:
		//UE_LOG(LogTemp, Warning, TEXT("Robot is interacting with player."));
		RotateToPlayer();
		break;

	case ERobotStates::Drone_Talk:
		//UE_LOG(LogTemp, Warning, TEXT("Robot is talking."));
		break;

	case ERobotStates::Drone_Loading:
		//UE_LOG(LogTemp, Warning, TEXT("Robot is loading."));
		break;

	case ERobotStates::Drone_Follow:
		//UE_LOG(LogTemp, Warning, TEXT("Robot is Following."));
		break;
	}
}

// Sets up player input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); // Calls the base SetupPlayerInputComponent function
}