// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WSGameServerStructures.generated.h"


USTRUCT(BlueprintType)
struct FSetClientIdRequest
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Event;
	UPROPERTY()
	int32 ID;
};

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()
	UPROPERTY()
	FString PlayerID;

	UPROPERTY()
	FVector Position;
};
