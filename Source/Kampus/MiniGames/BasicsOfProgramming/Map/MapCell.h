// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "MapCell.generated.h"

class AControlledRobot;
class AMapGenerator;
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

	UPROPERTY(Category="Mesh", EditDefaultsOnly)
	UStaticMeshComponent* BaseCellMesh;
	UPROPERTY(Category="Connector", EditDefaultsOnly)
	USceneComponent* ModificatorSceneComponent;

	UPROPERTY( Category="Mesh", EditDefaultsOnly)
	UStaticMeshComponent* WallMesh;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AControlledRobot> RobotSubclass;
	
	void CellTypeInit(int32 Index);

	AMapGenerator* ParrentMap;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
