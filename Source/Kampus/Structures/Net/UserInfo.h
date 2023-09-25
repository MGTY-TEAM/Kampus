// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "UserInfo.generated.h"


// Struct for storing user information and sent to the server.
USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()
	
	//Player nickname. Shows up in the game.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category= "User Info")
	FString UserName;
	
	//Player password.
	FString Password;

	//Player email address.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category= "User Info")
	FString Email;

	//Player login.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category= "User Info")
	FString Login;
};

