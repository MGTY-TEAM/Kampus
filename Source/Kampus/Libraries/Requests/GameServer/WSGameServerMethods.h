// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WSGameServerMethods.generated.h"

struct FPlayerInfo;
/**
 * 
 */
UCLASS()
class KAMPUS_API UWSGameServerMethods : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	static FString GetJsonStringByPlayerTransform(FVector UserPosition);
	static FString GetJsonStringByPlayerId(const FString& UserId);
	static TArray<FPlayerInfo> ParsePlayersInfo(const FString& JsonString);
};
