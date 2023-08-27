// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControlledRobot.generated.h"

class AMapCell;
UCLASS()
class KAMPUS_API AControlledRobot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AControlledRobot();

	UPROPERTY(EditDefaultsOnly, Category="Scene")
	USceneComponent* RootSceneComponent;
//Actions
	void MoveRobot();
	void RotateRight();
	void RotateLeft();
//Conditions
	bool IsWallForward();
	bool IsWallRight();
	bool IsWallLeft();

	bool IsEnd();
	AMapCell* CellPosition;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	bool bIsEnd;
};
