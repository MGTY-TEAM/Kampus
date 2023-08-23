// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCell.h"

#include "Components/StaticMeshComponent.h"


// Sets default values
AMapCell::AMapCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CellType = EMapCellType::EMCT_CLEAN;
	
	ModificatorSceneComponent = CreateDefaultSubobject<USceneComponent>("Modificator Scene Component");
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Wall Mesh");
	WallMesh->bVisible = false;
}

void AMapCell::CellTypeInit(int32 Index)
{
	switch (Index)
	{
	case(0):
		{
			CellType = EMapCellType::EMCT_CLEAN;
			break;
		}
	case(1):
		{
			CellType = EMapCellType::EMCT_WALL;
			WallMesh->bVisible = true;
			break;
		}
	case(2):
		{
			CellType = EMapCellType::EMCT_PLAYER;
			break;
		}
	case(3):
		{
			CellType = EMapCellType::EMCT_FINISH;
			break;
		}
	}
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
