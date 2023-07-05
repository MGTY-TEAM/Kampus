// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "HTTPRequestsLib.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(LogRequests, Log, All);
/**
 * 
 */
UCLASS()
class KAMPUS_API UHTTPRequestsLib : public UObject
{
	GENERATED_BODY()
public:
	static void AIMyLogicGetRequest(TFunction<void(const FString&) > CallBack,const FString& StringRequest);
};
