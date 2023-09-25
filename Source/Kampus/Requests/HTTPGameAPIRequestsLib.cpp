// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPGameAPIRequestsLib.h"

#include "GenericPlatformHttp.h"
#include "HttpModule.h"
#include "HttpRetrySystem.h"
#include "IHttpResponse.h"
#include "JsonObjectConverter.h"
#include "JsonReader.h"
#include "JsonSerializer.h"



void UHTTPGameAPIRequestsLib::GameAPILoginRequest(
	TFunction<void(const bool&, const FLoginResponse&, const FLoginErrorResponse&)> CallBack,
	const FLoginRequest& LoginRequest)
{
	FLoginResponse* LoginResponse;
	FLoginErrorResponse* LoginErrorResponse;
	FString URL = /*M_GameServerAPIAddress*/ + "login";

	FHttpModule* Module = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Module->CreateRequest();

	Request->OnProcessRequestComplete().BindLambda(
		[=](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			int32 ResponseCode = Response->GetResponseCode();
			switch (ResponseCode)
			{
			case 200:
				{
					if (FJsonObjectConverter::JsonObjectStringToUStruct<FLoginResponse>(
						Response->GetContentAsString(), LoginResponse, 0, 0))
					{
						CallBack(true, *LoginResponse, *LoginErrorResponse);
					}
				}
				break;
			case 400:
				{
					if (FJsonObjectConverter::JsonObjectStringToUStruct<FLoginErrorResponse>(
						Response->GetContentAsString(), LoginErrorResponse, 0, 0))
					{
						UE_LOG(HTTPGameApiLog, Error, TEXT("Server Error: %s"), *LoginErrorResponse->Error);
						CallBack(false, *LoginResponse, *LoginErrorResponse);
					}
				}
				break;
			}
		});

	FString RequestString;

	TSharedPtr<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	FJsonObjectConverter::UStructToJsonObjectString<FLoginRequest>(LoginRequest, RequestString);


	Request->SetURL(URL);
	Request->SetVerb(TEXT("Post"));
	Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
	Request->SetContentAsString(RequestString);
	Request->ProcessRequest();
}

void UHTTPGameAPIRequestsLib::GameAPIRegisterRequest(TFunction<void(const bool&, const FRegisterResponse& , const  FRegisterErrorResponse&)> CallBack,
                                                     const FRegisterRequest& RegisterRequest)
{
	FString URL = /*M_GameServerAPIAddress*/ + "register";
	FHttpModule* Module = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Module->CreateRequest();

	Request->OnProcessRequestComplete().BindLambda(
		[CallBack](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			int32 ResponseCode = Response->GetResponseCode();
			switch (ResponseCode)
			{
			case 200:
				{
					FRegisterResponse UserInfo;
					if (FJsonObjectConverter::JsonObjectStringToUStruct<FRegisterResponse>(
						Response->GetContentAsString(), &UserInfo, 0, 0))
					{
						UE_LOG(LogTemp, Log, TEXT("Response token: %s "), *UserInfo.Token);
					}
				}
				break;
			case 400:
				{
					FRegisterErrorResponse ErrorResponse;
					if (FJsonObjectConverter::JsonObjectStringToUStruct<FRegisterErrorResponse>(
						Response->GetContentAsString(), &ErrorResponse, 0, 0))
						UE_LOG(HTTPGameApiLog, Error, TEXT("Server Error: %s"), *ErrorResponse.Error);
					break;
				}
			}
		});

	FString RequestString;

	TSharedPtr<FJsonObject> RequestObject = MakeShared<FJsonObject>();
	FJsonObjectConverter::UStructToJsonObjectString<FRegisterRequest>(RegisterRequest, RequestString);


	Request->SetURL(URL);
	Request->SetVerb(TEXT("Post"));
	Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
	Request->SetContentAsString(RequestString);
	Request->ProcessRequest();
}
