// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneAIController.h"

#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

ADroneAIController::ADroneAIController(FObjectInitializer const& Object_Initializer)
{
}

void ADroneAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BTree);
	BehaviorTreeComponent-> StartTree(*BTree);
}

void ADroneAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*auto const NPC = this->GetPawn();
	auto const Drone = Cast<ADrone>(NPC);

	if(Drone)
	{
		float TimeSeconds = GetWorld()->GetTimeSeconds();
		float Movement = (sin(TimeSeconds * Frecuency) * Amplitude) + Drone->Robot->GetComponentLocation().Z;
		Drone->Robot->SetWorldLocation(FVector(Drone->Robot->GetComponentLocation().X, Drone->Robot->GetComponentLocation().Y, Movement));
	}*/
	
	
}

void ADroneAIController::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
}
