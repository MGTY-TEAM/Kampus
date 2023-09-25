// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePlayerGameMode.h"

#include "Requests/HTTPGameAPIRequestsLib.h"

void ASinglePlayerGameMode::OnBeginPlay()
{
	FLoginRequest Request;
	Request.Login = "login";
	Request.Password = "1234";
	UHTTPGameAPIRequestsLib::GameAPILoginRequest([](const bool& ResponseState, const FLoginResponse& LoginResponse, const  FLoginErrorResponse& LoginErrorResponse)
	{
		if (ResponseState)
		{
			UE_LOG(LogTemp, Warning, TEXT("Login Response: %s"), *LoginResponse.Token);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Login Error: %s"), *LoginErrorResponse.Error)
		}
	}, Request);
}
