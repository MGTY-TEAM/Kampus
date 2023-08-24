// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCell.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MiniGames/BasicsOfProgramming/ControlledRobot.h"


// Sets default values
AMapCell::AMapCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	


	BaseCellMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Cell Mesh");
	SetRootComponent(BaseCellMesh);
	
	ModificatorSceneComponent = CreateDefaultSubobject<USceneComponent>("Modificator Scene Component");
	ModificatorSceneComponent->SetupAttachment(BaseCellMesh);
	
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Wall Mesh");
	WallMesh->SetupAttachment(BaseCellMesh);
	WallMesh->bVisible = false;
	
	CellType = EMapCellType::EMCT_CLEAN;
}

void AMapCell::CellTypeInit(int32 Index)
{
	switch (Index)
	{
	case(0):
		{
			CellType = EMapCellType::EMCT_CLEAN;
			WallMesh->bVisible = false;
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
			AControlledRobot* Robot = Cast<AControlledRobot>(UGameplayStatics::GetActorOfClass(GetWorld(), RobotSubclass));
			Robot->SetActorLocation(GetActorLocation());
			break;
		}
	case(3):
		{
			CellType = EMapCellType::EMCT_FINISH;
			WallMesh->bVisible = true;
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
