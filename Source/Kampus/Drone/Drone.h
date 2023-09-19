// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotStates.h"
#include "Core/BaseFirstPersonCharacter.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interaction/Interactable.h"

#include "Drone.generated.h"

UCLASS()
class KAMPUS_API ADrone : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADrone();
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* Robot;
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* Face;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin")
	float Frecuency1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin")
	float Amplitude1;

	ERobotStates CurrentState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="KeyWords")
	TArray<FText> KeyWords;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> BlueprintChatClass;

	ABaseFirstPersonCharacter* PlayerCharacter;

	FTimerHandle IdleAnim_Timer;
	FTimerHandle RotateToPlayer_Timer;

	virtual void Interact() override;
	virtual void EndInteract() override;
	void ChangeState(ERobotStates State, float Duration = 0);

	void IdleAnim();
	void RotateToPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
