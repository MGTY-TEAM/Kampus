// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapCell.generated.h"
UENUM(BlueprintType)
enum class EMapCellType : uint8
{
	EMCT_PLAYER = 0 UMETA(DisplayName = "Player"),  
	EMCT_FINISH = 1 UMETA(DisplayName = "Finish"),  
	EMCT_WALL = 2 UMETA(DisplayName = "Wall"),
	EMCT_CLEAN = 3 UMETA(DisplayName = "Clean")
};
UCLASS()
class KAMPUS_API AMapCell : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapCell();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EMapCellType CellType;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
