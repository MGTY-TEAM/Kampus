// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiniGames/BasicsOfProgramming/Database/MiniGamesDatabase.h"
#include "MapGenerator.generated.h"

class AMapCell;
class AControlledRobot;

UCLASS()
class KAMPUS_API AMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapGenerator();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapCell> CellSubClass;
	TPair<int32, int32> GetCellIndexesByCell(AMapCell* Cell);
	TArray<TArray<AMapCell*>> MapCells;
	bool CanMoveToCoordinate(int32 X, int32 Y, AControlledRobot* Robot);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostLoad() override;
	virtual void PostInitializeComponents() override;

	
	virtual void SaveMap();
	
	virtual bool LoadMap();
private:
	
	TArray<TArray<int32>> SerialisedMap;
	MiniGamesDatabase* Database;
};
