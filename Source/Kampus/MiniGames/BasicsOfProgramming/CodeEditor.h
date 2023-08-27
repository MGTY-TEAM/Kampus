// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/CodeEntity.h"
#include "CodeEditor.generated.h"

/**
 * 
 */
class UCodeListing;
class UButton;

class AControlledRobot;
UCLASS()
class KAMPUS_API UCodeEditor : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UCodeListing* MainCodeListing;

	UPROPERTY(meta = (BindWidget))
	UButton* RunButton;

	UPROPERTY(EditDefaultsOnly)
	int32 StepCountLimit{32};
	
protected:
	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
	virtual void ParseCode(UCodeListing* CodeListing);
	UFUNCTION()
	virtual void RunButtonOnClick();
	void OnEnding();

	int32 StepCount;
	AControlledRobot* ControlledRobot;

	bool RobotIsEnding;
};
