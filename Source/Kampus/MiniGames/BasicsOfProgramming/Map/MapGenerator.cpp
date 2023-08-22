// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"

#include "Paths.h"

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
		
	}
	
	/*SaveMap();*/
}

void AMapGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMapGenerator::SaveMap()
{
	TArray<TArray<int32>> Map;
	Map.Init(TArray<int32>(), 10);
	for (int j = 0; j < Map.Num(); j++)
	{
		for (int i = 0;  i < 10; i++)
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
