// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"



ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

