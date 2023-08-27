// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlledRobot.h"

#include "Map/MapCell.h"
#include "Map/MapGenerator.h"


// Sets default values
AControlledRobot::AControlledRobot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>("RootScene");
	SetRootComponent(RootSceneComponent);
}

void AControlledRobot::MoveRobot()
{
	bool MoveResult = false;
	float X = GetActorForwardVector().X;
	float Y = GetActorForwardVector().Y;
	
	if (FMath::IsNearlyEqual(X, 1, 0.01f) || FMath::IsNearlyEqual(X, -1, 0.01f))
	{
		if (FMath::IsNearlyEqual(X, 1, 0.01f))
		{
			MoveResult = CellPosition->ParrentMap->CanMoveToCoordinate(1, 0, this);
		}
		else
		{
			MoveResult = CellPosition->ParrentMap->CanMoveToCoordinate(-1, 0, this);
		}
	}
	else
	{
		if (FMath::IsNearlyEqual(Y, 1, 0.01f))
		{
			MoveResult = CellPosition->ParrentMap->CanMoveToCoordinate(0, 1, this);
		}
		else
		{
			MoveResult = CellPosition->ParrentMap->CanMoveToCoordinate(0, -1, this);
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
		UE_LOG(LogTemp, Warning, TEXT("Robot do not Move"))
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
	UE_LOG(LogTemp, Warning, TEXT("Forward Vector (%f, %f, %f)"), GetActorForwardVector().X, GetActorForwardVector().Y,
	   GetActorForwardVector().Z);
}

bool AControlledRobot::IsWallForward()
{
	float X = GetActorForwardVector().X;
	float Y = GetActorForwardVector().Y;
	bool Result;
	if (FMath::IsNearlyEqual(X, 1, 0.01f) || FMath::IsNearlyEqual(X, -1, 0.01f))
	{
		if (FMath::IsNearlyEqual(X, 1, 0.01f))
		{
			Result = CellPosition->ParrentMap->IsWall(1, 0, this);
		}
		else
		{
			Result = CellPosition->ParrentMap->IsWall(-1, 0, this);
		}
	}
	else
	{
		if (FMath::IsNearlyEqual(Y, 1, 0.01f))
		{
			Result = CellPosition->ParrentMap->IsWall(0, 1, this);
		}
		else
		{
			Result = CellPosition->ParrentMap->IsWall(0, -1, this);
		}
	}
	return Result;
}

bool AControlledRobot::IsWallRight()
{
	float X = GetActorRightVector().X;
	float Y = GetActorRightVector().Y;
	bool Result;
	if (FMath::IsNearlyEqual(X, 1, 0.01f) || FMath::IsNearlyEqual(X, -1, 0.01f))
	{
		if (FMath::IsNearlyEqual(X, 1, 0.01f))
		{
			Result = CellPosition->ParrentMap->IsWall(1, 0, this);
		}
		else
		{
			Result = CellPosition->ParrentMap->IsWall(-1, 0, this);
		}
	}
	else
	{
		if (FMath::IsNearlyEqual(Y, 1, 0.01f))
		{
			Result = CellPosition->ParrentMap->IsWall(0, 1, this);
		}
		else
		{
			Result = CellPosition->ParrentMap->IsWall(0, -1, this);
		}
	}
	return Result;
}

bool AControlledRobot::IsWallLeft()
{
	float X = (-GetActorRightVector()).X;
	float Y = (-GetActorRightVector()).Y;
	bool Result;
	if (FMath::IsNearlyEqual(X, 1, 0.01f) || FMath::IsNearlyEqual(X, -1, 0.01f))
	{
		if (FMath::IsNearlyEqual(X, 1, 0.01f))
		{
			Result = CellPosition->ParrentMap->IsWall(1, 0, this);
		}
		else
		{
			Result = CellPosition->ParrentMap->IsWall(-1, 0, this);
		}
	}
	else
	{
		if (FMath::IsNearlyEqual(Y, 1, 0.01f))
		{
			Result = CellPosition->ParrentMap->IsWall(0, 1, this);
		}
		else
		{
			Result = CellPosition->ParrentMap->IsWall(0, -1, this);
		}
	}
	return Result;
}

bool AControlledRobot::IsEnd()
{
	if (CellPosition->CellType == EMapCellType::EMCT_FINISH)
		return true;
	return false;
}

// Called when the game starts or when spawned
void AControlledRobot::BeginPlay()
{
	Super::BeginPlay();
}
