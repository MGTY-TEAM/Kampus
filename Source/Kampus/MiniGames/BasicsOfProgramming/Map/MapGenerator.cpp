// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"

#include "Paths.h"
#include "Engine/World.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	Database = new MiniGamesDatabase(FPaths::GameSourceDir() + "Kampus/Data/SQLiteMiniGamesDatabase.db",
									 ESQLiteDatabaseOpenMode::ReadWrite);


	if (Database)
	{
		TArray<TArray<int32>> SerialisedMap = Database->LoadMap(0);
		if (SerialisedMap.Num() != 0)
		{
			this->SerialisedMap = SerialisedMap;

			MapCells.Init(TArray<AMapCell*>(), SerialisedMap.Num());
			for (int i = 0; i < MapCells.Num(); i++)
			{
				MapCells[i].Init(nullptr, SerialisedMap[i].Num());
			}
		}
	}

	for (int i = 0; i < MapCells.Num(); i++)
	{
		for (int j = 0; j < MapCells[i].Num(); j++)
		{
			FActorSpawnParameters SpawnParameters;
			MapCells[i][j] = GetWorld()->SpawnActor<AMapCell>(CellSubClass, SpawnParameters);
			MapCells[i][j]->CellTypeInit(SerialisedMap[i][j]);
			MapCells[i][j]->SetActorLocation(FVector(GetActorLocation().X + i * 100, GetActorLocation().Y + j * 100,
													 GetActorLocation().Z));
			MapCells[i][j]->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
	

	
}

void AMapGenerator::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
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


void AMapGenerator::SaveMap()
{
	TArray<TArray<int32>> Map;
	Map.Init(TArray<int32>(), 10);
	for (int j = 0; j < Map.Num(); j++)
	{
		for (int i = 0; i < 10; i++)
		{
			Map[j].Add(0);
		}
	}
	bool SaveState = Database->SaveMap(0, Map);
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Save State:(%hdd)"), SaveState);
#endif
}


// Called every frame
