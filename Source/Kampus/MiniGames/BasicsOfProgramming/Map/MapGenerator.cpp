// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"

#include "MapCell.h"
#include "Paths.h"
#include "Engine/World.h"
#include "MiniGames/BasicsOfProgramming/ControlledRobot.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

bool AMapGenerator::CanMoveToCoordinate(int32 deltaX, int32 deltaY, AControlledRobot* Robot)
{
	if (!Robot)
		return false;

	int32 sizeX = MapCells.Num();
	int32 sizeY = MapCells[0].Num();

	int32 X;
	int32 Y;

	for (int i = 0; i < MapCells.Num(); i++)
	{
		for (int j = 0; j < MapCells[j].Num(); j++)
		{
			if (MapCells[i][j] == Robot->CellPosition)
			{
				X = i;
				Y = j;
			}
		}
	}

	if ((X + deltaX > 0) && (X + deltaX < sizeX) && (Y + deltaY > 0) && (Y + deltaY < sizeY))
	{
		AMapCell* NextCell = MapCells[X + deltaX][Y + deltaY];

		if (NextCell->CellType != EMapCellType::EMCT_WALL)
		{
			return Robot->SetActorLocation(NextCell->GetActorLocation());
		}
	}

	return false;
}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

	Database = new MiniGamesDatabase(FPaths::GameSourceDir() + "Kampus/Data/SQLiteMiniGamesDatabase.db",
	                                 ESQLiteDatabaseOpenMode::ReadWrite);


	//SaveMap();
	// Fill MapCells And SerialisedMap
	if (LoadMap())
	{
		//Create Square Field of MapCells
		for (int i = 0; i < MapCells.Num(); i++)
		{
			for (int j = 0; j < MapCells[i].Num(); j++)
			{
				FActorSpawnParameters SpawnParameters;
				MapCells[i][j] = GetWorld()->SpawnActor<AMapCell>(CellSubClass, SpawnParameters);
				MapCells[i][j]->ParrentMap = this;
				MapCells[i][j]->SetActorLocation(FVector(GetActorLocation().X + (i - 1) * 100,
				                                         GetActorLocation().Y + j * 100,
				                                         GetActorLocation().Z));
				MapCells[i][j]->CellTypeInit(SerialisedMap[i][j]);
				MapCells[i][j]->SetActorLocation(FVector(GetActorLocation().X + i * 100, GetActorLocation().Y + j * 100,
				                                         GetActorLocation().Z));


				MapCells[i][j]->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			}
		}
	}
}

void AMapGenerator::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//Delete Database(VERY IMPORTANT!!!)
	delete Database;
}

void AMapGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMapGenerator::PostLoad()
{
	Super::PostLoad();
}

void AMapGenerator::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

TPair<int32, int32> AMapGenerator::GetCellIndexesByCell(AMapCell* Cell)
{
	for (int i = 0; i < MapCells.Num(); i++)
	{
		for (int j = 0; j < MapCells.Num(); j++)
		{
			if (MapCells[i][j] == Cell)
			{
				return TPair<int32, int32>(i, j);
			}
		}
	}
	return TPair<int32, int32>();
}


void AMapGenerator::SaveMap()
{
	TArray<TArray<int32>> Map = {
		{0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0},
		{1, 2, 0, 3, 1},
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 0},
	};
	bool SaveState = Database->SaveMap(1, Map);
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Save State:(%hdd)"), SaveState);
#endif
}

bool AMapGenerator::LoadMap()
{
	if (Database)
	{
		TArray<TArray<int32>> SerialisedMap = Database->LoadMap(1);
		if (SerialisedMap.Num() != 0)
		{
			this->SerialisedMap = SerialisedMap;

			MapCells.Init(TArray<AMapCell*>(), SerialisedMap.Num());
			for (int i = 0; i < MapCells.Num(); i++)
			{
				MapCells[i].Init(nullptr, SerialisedMap[i].Num());
			}
			return true;
		}
		return false;
	}
	return false;
}


// Called every frame
