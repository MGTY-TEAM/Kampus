// Fill out your copyright notice in the Description page of Project Settings.
// https://github.com/MEgorov4/Kampus/wiki/HTTP-Requests-System
#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "HTTPAiMyLogicRequestsLib.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(LogRequests, Log, All);
 
/**
 * 
 */
UCLASS()
class KAMPUS_API UHTTPAiMyLogicRequestsLib : public UObject
{
	GENERATED_BODY()

public:
	static void AIMyLogicGetRequest(TFunction<void(const FString&)> CallBack, const FString& StringRequest, const FString& URL);
};
