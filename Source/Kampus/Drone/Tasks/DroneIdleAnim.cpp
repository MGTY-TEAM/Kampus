// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneIdleAnim.h"

#include "Drone/Drone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Drone/DroneAIController.h"

UDroneIdleAnim::UDroneIdleAnim(FObjectInitializer const& ObjectInitializer)
{
	
}

EBTNodeResult::Type UDroneIdleAnim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	auto const Controller = Cast<ADroneAIController>(OwnerComp.GetAIOwner());
	auto const NPC = Controller-> GetPawn();
	auto const Drone = Cast<ADrone>(NPC);
	
	if(Drone)
	{
		float TimeSeconds = GetWorld()->GetTimeSeconds();
		float Movement = (sin(TimeSeconds * Frecuency) * Amplitude) + Drone->Robot->GetComponentLocation().Z;
		Drone->Robot->SetWorldLocation(FVector(Drone->Robot->GetComponentLocation().X, Drone->Robot->GetComponentLocation().Y, Movement));
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
