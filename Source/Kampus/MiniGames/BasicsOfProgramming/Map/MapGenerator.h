// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapCell.h"
#include "GameFramework/Actor.h"
#include "MiniGames/BasicsOfProgramming/Database/MiniGamesDatabase.h"
#include "MapGenerator.generated.h"

UCLASS()
class KAMPUS_API AMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapGenerator();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapCell> CellSubClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostLoad() override;
	virtual void PostInitializeComponents() override;
	virtual void SaveMap();


private:
	TArray<TArray<AMapCell*>> MapCells;
	TArray<TArray<int32>> SerialisedMap;
	MiniGamesDatabase* Database;
};
