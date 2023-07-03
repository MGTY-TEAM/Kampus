// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneIdleAnim.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Drone/DroneAIController.h"

UDroneIdleAnim::UDroneIdleAnim(FObjectInitializer const& ObjectInitializer)
{
	
}

EBTNodeResult::Type UDroneIdleAnim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
