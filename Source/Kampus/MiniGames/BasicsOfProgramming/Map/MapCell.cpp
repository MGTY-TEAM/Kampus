// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCell.h"


// Sets default values
AMapCell::AMapCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CellType = EMapCellType::EMCT_CLEAN;
}

// Called when the game starts or when spawned
void AMapCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

