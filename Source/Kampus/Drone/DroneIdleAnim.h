// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"

#include "DroneIdleAnim.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class KAMPUS_API UDroneIdleAnim : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UDroneIdleAnim(FObjectInitializer const& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin")
	float Frecuency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin")
	float Amplitude;
};
