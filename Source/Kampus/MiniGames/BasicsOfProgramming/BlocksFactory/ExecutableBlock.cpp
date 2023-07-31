// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecutableBlock.h"


AExecutableBlock::AExecutableBlock()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AExecutableBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExecutableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

