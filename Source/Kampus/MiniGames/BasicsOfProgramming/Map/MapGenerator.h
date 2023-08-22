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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	virtual void SaveMap();
	
private:
	TArray<TArray<AMapCell*>> MapCells;
	MiniGamesDatabase* Database;
};
