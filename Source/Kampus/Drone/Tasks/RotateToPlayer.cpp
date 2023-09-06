// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateToPlayer.h"

#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Drone/DroneAIController.h"
#include "GameFramework/PlayerController.h"

URotateToPlayer::URotateToPlayer(FObjectInitializer const& ObjectInitializer)
{
	
}

EBTNodeResult::Type URotateToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Controller = Cast<ADroneAIController>(OwnerComp.GetAIOwner());
	auto const NPC = Controller->GetPawn();
	auto const Drone = Cast<ADrone>(NPC);
	auto const PlayerCharacter = Cast<ABaseFirstPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	bool finish = false;
	/*if(Drone != nullptr && Drone->CurrentState == ERobotStates::Drone_PlayerInteract)
	{
		// If the state is "PlayerInteract", then the following code is executed
		// Makes the drone always look at the player
		
		FVector StartLocation = Drone->GetCapsuleComponent()->GetComponentLocation(); // Starting position of the drone
		FVector TargetLocation = PlayerCharacter->GetActorLocation(); // Player's position

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation); // Calculates the look-at vector from the drone to the player
	
		FRotator StartRotation = Drone->GetCapsuleComponent()->GetComponentRotation(); // Starting rotation of the drone
		FRotator EndRotation = LookAtRotation; // Final rotation - look at the player

		// Calculates the interpolated rotation
		FRotator InterpolatedRotation = FMath::RInterpTo(StartRotation, EndRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
		// Applies the interpolated rotation to the capsule component
		Drone->GetCapsuleComponent()->SetWorldRotation(InterpolatedRotation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}*/

	/*RotationToPlayer(OwnerComp, &finish);

	if(finish == true)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}*/
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

void URotateToPlayer::RotationToPlayer(UBehaviorTreeComponent& OwnerComp, bool* success)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Rotate"));

	auto const Controller = Cast<ADroneAIController>(OwnerComp.GetAIOwner());
	auto const NPC = Controller->GetPawn();
	auto const Drone = Cast<ADrone>(NPC);
	auto const PlayerCharacter = Cast<ABaseFirstPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, FName("RotationToPlayer"), success);
	// If the state is "PlayerInteract", then the following code is executed
	// Makes the drone always look at the player
	
	FVector StartLocation = Drone->GetCapsuleComponent()->GetComponentLocation(); // Starting position of the drone
	FVector TargetLocation = PlayerCharacter->GetActorLocation(); // Player's position

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation); // Calculates the look-at vector from the drone to the player

	FRotator StartRotation = Drone->GetCapsuleComponent()->GetComponentRotation(); // Starting rotation of the drone
	FRotator EndRotation = LookAtRotation; // Final rotation - look at the player

	// Calculates the interpolated rotation
	FRotator InterpolatedRotation = FMath::RInterpTo(StartRotation, EndRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
	// Applies the interpolated rotation to the capsule component
	Drone->GetCapsuleComponent()->SetWorldRotation(InterpolatedRotation);

	if (Drone->GetCapsuleComponent()->GetComponentRotation() == EndRotation)
	{
		*success = true;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(UpdateTimerHandle, Delegate, TimerInterval, false);
	}*/
}

