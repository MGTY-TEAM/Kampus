// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BasicsOfProgrammingGameMode.generated.h"

class UUserWidget;
UCLASS()
class KAMPUS_API ABasicsOfProgrammingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasicsOfProgrammingGameMode();
	
	UPROPERTY(Category="Startup", EditDefaultsOnly)
	TSubclassOf<UUserWidget> StartupWidget;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
