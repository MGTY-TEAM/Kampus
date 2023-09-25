// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "HTTPGameAPIRequestsLib.generated.h"

/**
 * 
 */

DEFINE_LOG_CATEGORY_STATIC(HTTPGameApiLog, Log, All);

USTRUCT(BlueprintType)
struct FLoginRequest
{
	GENERATED_BODY()
	FString Login;
	FString Password;
};

USTRUCT(BlueprintType)
struct FLoginResponse 
{
	GENERATED_BODY()
	FString Token;
};

USTRUCT(BLueprintType)
struct FLoginErrorResponse 
{
	GENERATED_BODY()
	FString Error;
};

USTRUCT(BlueprintType)
struct FRegisterRequest
{
	GENERATED_BODY()

	FString Username;
	FString Email;
	FString Login;
	FString Password;
};

USTRUCT(BlueprintType)
struct FRegisterResponse 
{
	GENERATED_BODY()
	FString Token;
};

USTRUCT(BlueprintType)
struct FRegisterErrorResponse 
{
	GENERATED_BODY()
	FString Error;
};

UCLASS()
class KAMPUS_API UHTTPGameAPIRequestsLib : public UObject
{
	GENERATED_BODY()

public:
	
	/**
	* @brief Create HTTP request to login on the GameAPI server.
	* @param CallBack Delegate to call when the request is done.
	* @param LoginRequest Structure containing the login request.
	*/
	/*UFUNCTION(BlueprintCallable, Category = "GameAPI")*/
	static void GameAPILoginRequest(TFunction<void(const bool&, const FLoginResponse& , const  FLoginErrorResponse&)> CallBack, const FLoginRequest& LoginRequest);
	
	/**
	* @brief Create HTTP request to register on the GameAPI server.
	* @param CallBack Delegate to call when the request is done.
	* @param LoginRequest Structure containing the register request.
	*/
	/*UFUNCTION(BlueprintCallable, Category= "GameAPI")*/
	static void GameAPIRegisterRequest(TFunction<void(const bool&, const FRegisterResponse& , const  FRegisterErrorResponse&)> CallBack,
	                                   const FRegisterRequest& RegisterRequest);
	
	/// GameAPI server address.
	/*static FString M_GameServerAPIAddress;*/
};





