// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControlledRobot.generated.h"

UCLASS()
class KAMPUS_API AControlledRobot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AControlledRobot();
//Actions
	void Move();
	void RotateRight();
	void RotateLeft();
//Conditions
	bool IsWallForward();
	bool IsWallRight();
	bool IsWallLeft();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
