// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseFirstPersonCharacter.generated.h"

UCLASS()
class KAMPUS_API ABaseFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseFirstPersonCharacter();

	UPROPERTY(Category="Movement", EditDefaultsOnly)
	float Speed;
	UPROPERTY(Category="Movement", EditDefaultsOnly)
	float MouseSpeed;

	UPROPERTY(Category="Interaction", EditDefaultsOnly)
	float InteractionDistance;

	UPROPERTY(Category="Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(Category="Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

protected:
	virtual void BeginPlay() override;
	void AILogicCallBack(FString Answer);

	virtual void Interact();

	virtual void MoveForward(float value);
	virtual void MoveRight(float value);
	virtual void LookUp(float value);
	virtual void LookRight(float value);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
