// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlledRobot.h"

#include "Components/StaticMeshComponent.h"
#include "Map/MapCell.h"
#include "Map/MapGenerator.h"


// Sets default values
AControlledRobot::AControlledRobot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootScene");
}

void AControlledRobot::Move()
{
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Robot Move"))
#endif
	const FVector ForwardVector = GetActorForwardVector();
	
	bool MoveResult;
	//Find Way Robot Look

	int32 ForwardX = static_cast<int32>(ForwardVector.X);
	int32 ForwardY =  static_cast<int32>(ForwardVector.Y);

	if (ForwardX != 0)
	{
		if (ForwardX == 1)
		{
			MoveResult = CellPosition->ParrentMap->CanMoveToCoordinate(1, 0,this);
		}
		else
		{
			MoveResult = CellPosition->ParrentMap->CanMoveToCoordinate(-1, 0,this);
		}
	}
	else
	{
		if (ForwardY == 1)
		{
			MoveResult = CellPosition->ParrentMap->CanMoveToCoordinate(0, 1,this);
		}
		else
		{
			MoveResult = CellPosition->ParrentMap->CanMoveToCoordinate(0, -1,this);
		}
	}

	if (MoveResult)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Robot Move"))
#endif
	}
	else
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Robot do notd Move"))
#endif
	}
}

void AControlledRobot::RotateRight()
{
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Robot Rotate Right"))
#endif
	AddActorWorldRotation(FRotator(0.f, 90.f, 0.f));
	UE_LOG(LogTemp, Warning, TEXT("Forward Vector (%f, %f, %f)"), GetActorForwardVector().X, GetActorForwardVector().Y,
	       GetActorForwardVector().Z);
}

void AControlledRobot::RotateLeft()
{
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Robot Rotate Left"))
#endif
	AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
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
