// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HTTPGameAPIStructures.generated.h"



USTRUCT(BlueprintType)
struct FLoginRequest
{
	GENERATED_BODY()
	UPROPERTY()
	FString Login;
	UPROPERTY()
	FString Password;
};

USTRUCT(BlueprintType)
struct FLoginResponse
{
	GENERATED_BODY()
	UPROPERTY()
	FString Token;
};

USTRUCT(BlueprintType)
struct FLoginErrorResponse
{
	GENERATED_BODY()
	UPROPERTY()
	FString Error;
};


USTRUCT(BlueprintType)
struct FRegisterRequest
{
	GENERATED_BODY()
	UPROPERTY()
	FString Nickname;
	UPROPERTY()
	FString Email;
	UPROPERTY()
	FString Login;
	UPROPERTY()
	FString Password;
};

USTRUCT(BlueprintType)
struct FRegisterResponse
{
	GENERATED_BODY()
	UPROPERTY()
	FString Token;
};

USTRUCT(BlueprintType)
struct FRegisterErrorResponse
{
	GENERATED_BODY()
	UPROPERTY()
	FString Error;
};



USTRUCT(BlueprintType)
struct FUserInfoRequest
{
	GENERATED_BODY()
	UPROPERTY()
	FString Token;
};
USTRUCT(BlueprintType)
struct FUserInfoResponse
{
	GENERATED_BODY()
	UPROPERTY()
	FString Nickname;
	FString Email;
};
USTRUCT(BlueprintType)
struct FUserInfoErrorResponse
{
	GENERATED_BODY()
	FString Error;
};
