// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseFirstPersonCharacter.generated.h"

UCLASS()
class KAMPUS_API ABaseFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseFirstPersonCharacter();
	UPROPERTY(EditInstanceOnly)
	float Speed;
	UPROPERTY(EditInstanceOnly)
	float MouseSpeed;
protected:
	virtual void BeginPlay() override;
	/*Keyboard Events*/
	virtual void MoveForward(float value);
	virtual void MoveRight(float value);
	/*Mouse Events*/
	virtual void LookUp(float value);
	virtual void LookRight(float value);
public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
