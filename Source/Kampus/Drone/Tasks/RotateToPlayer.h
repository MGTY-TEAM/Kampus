// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Drone/Drone.h"
#include "RotateToPlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class KAMPUS_API URotateToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	URotateToPlayer(FObjectInitializer const& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void RotationToPlayer(UBehaviorTreeComponent& OwnerComp, bool* success);

	float MyTimer = 0.0f;
	float TimerInterval = 1.0f;

	FTimerHandle UpdateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin")
	float RotationSpeed;
};
