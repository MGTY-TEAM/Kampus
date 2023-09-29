// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StartupEntryGameMode.generated.h"

class UEntryWidget;

UCLASS()
class KAMPUS_API AStartupEntryGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AStartupEntryGameMode();

	UPROPERTY(EditDefaultsOnly, Category = "WidgetClasses")
	TSubclassOf<UEntryWidget> EntryWidgetClass;
	
protected:

	virtual void BeginPlay() override;

private:
	UEntryWidget* M_EntryWidget;
	
	UFUNCTION()
	void OnEntryWidgetExecute(const FString& Token);
};
