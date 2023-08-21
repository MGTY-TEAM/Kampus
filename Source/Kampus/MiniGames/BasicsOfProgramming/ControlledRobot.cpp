// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlledRobot.h"


// Sets default values
AControlledRobot::AControlledRobot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AControlledRobot::Move()
{
#if WITH_EDITOR
UE_LOG(LogTemp, Warning, TEXT("Robot Move"))
#endif
	
}

void AControlledRobot::RotateRight()
{
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Robot Rotate Right"))
#endif
}

void AControlledRobot::RotateLeft()
{
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Robot Rotate Left"))
#endif
}

bool AControlledRobot::IsWallForward()
{
	return false;
}

bool AControlledRobot::IsWallRight()
{
	return false;
}

bool AControlledRobot::IsWallLeft()
{
	return false;
}

// Called when the game starts or when spawned
void AControlledRobot::BeginPlay()
{
	Super::BeginPlay();
	
}
