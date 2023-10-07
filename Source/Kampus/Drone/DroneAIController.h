// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DroneAIController.generated.h"

/**
 * 
 */
UCLASS()
class KAMPUS_API ADroneAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADroneAIController(FObjectInitializer const& Object_Initializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void OnPossess(APawn* const InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin")
	float Frecuency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin")
	float Amplitude;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	UBehaviorTree* BTree;
};
