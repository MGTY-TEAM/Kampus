// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPGameAPIRequestsLib.h"

#include "GenericPlatformHttp.h"
#include "HTTPGameAPIStructures.h"
#include "HttpModule.h"
#include "HttpRetrySystem.h"
#include "IHttpResponse.h"
#include "JsonObjectConverter.h"


void UHTTPGameAPIRequestsLib::GameAPILoginRequest(
	TFunction<void(const bool&, const FLoginResponse&, const FLoginErrorResponse&)> CallBack,
	const FLoginRequest& LoginRequest)
{
	
	FString URL = "http://localhost:3000/api/login";

	FHttpModule* Module = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Module->CreateRequest();

	Request->OnProcessRequestComplete().BindLambda(
		[=](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			const int32 ResponseCode = Response->GetResponseCode();
			const FString JsonString = Response->GetContentAsString();
			
			switch (ResponseCode)
			{
			case 200:
				{
					FLoginResponse LoginResponse;
					GetStructFromJsonString(JsonString, LoginResponse);
					UE_LOG(HTTPGameApiLog, Warning, TEXT("Login Response Token: %s"), *LoginResponse.Token);

					CallBack(true, LoginResponse, FLoginErrorResponse());
					break;
				}
			case 400:
				{
					FLoginErrorResponse LoginErrorResponse;
					GetStructFromJsonString(JsonString, LoginErrorResponse);
					UE_LOG(HTTPGameApiLog, Warning, TEXT("Login Error: %s"), *LoginErrorResponse.Error)
					CallBack(false, FLoginResponse(), LoginErrorResponse);
					break;
				}
			default:
					UE_LOG(HTTPGameApiLog, Warning, TEXT("Undefined Response Code: %d"), ResponseCode);
				break;
			}
		});
	
	FString RequestString;
	if (GetJsonStringFromStruct(LoginRequest,RequestString))
	{
		Request->SetURL(URL);
		Request->SetVerb(TEXT("Post"));
		Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
		Request->SetHeader(TEXT("Accept"),TEXT("application/json"));
		Request->SetContentAsString(RequestString);
		Request->ProcessRequest();
	}
}

void UHTTPGameAPIRequestsLib::GameAPIRegisterRequest(
	TFunction<void(const bool&, const FRegisterResponse&, const FRegisterErrorResponse&)> CallBack,
	const FRegisterRequest& RegisterRequest)
{
	FString URL = "http://localhost:3000/api/register";
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
					FRegisterResponse RegisterResponse;
					GetStructFromJsonString(Response->GetContentAsString(), RegisterResponse);
					UE_LOG(HTTPGameApiLog, Log, TEXT("Register Response token: %s "), *RegisterResponse.Token);
					CallBack(true, RegisterResponse, FRegisterErrorResponse());
				}
				break;
			case 400:
				{
					FRegisterErrorResponse ErrorResponse;
					GetStructFromJsonString(Response->GetContentAsString(), ErrorResponse);
					UE_LOG(HTTPGameApiLog, Error, TEXT("Register Error: %s"), *ErrorResponse.Error);
					CallBack(true, FRegisterResponse(), ErrorResponse);
					break;
				}
			default:
				UE_LOG(HTTPGameApiLog, Error, TEXT("Unknown response code: %d"), ResponseCode);
				break;
			}
		});

	FString RequestString;
	if(GetJsonStringFromStruct(RegisterRequest, RequestString))
	{
		Request->SetURL(URL);
		Request->SetVerb(TEXT("Post"));
		Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
		Request->SetContentAsString(RequestString);
		Request->ProcessRequest();
	}
}

void UHTTPGameAPIRequestsLib::GameAPIUserInfoRequest(
	TFunction<void(const bool&, const FUserInfoResponse&, const FUserInfoErrorResponse&)> CallBack,
	const FUserInfoResponse& UserInfoRequest)
{
	FString URL = "http://localhost:3000/api/user-info";
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
					FUserInfoResponse UserInfoResponse;
					GetStructFromJsonString(Response->GetContentAsString(), UserInfoResponse);
					UE_LOG(HTTPGameApiLog, Log, TEXT("User Info Response Nickname: %s "), *UserInfoResponse.Nickname);
					CallBack(true, UserInfoResponse, FUserInfoErrorResponse());
				}
				break;
			case 400:
				{
					FUserInfoErrorResponse ErrorResponse;
					GetStructFromJsonString(Response->GetContentAsString(), ErrorResponse);
					UE_LOG(HTTPGameApiLog, Error, TEXT("User Info Response Error: %s"), *ErrorResponse.Error);
					CallBack(true, FUserInfoResponse(), ErrorResponse); 
					break;
				}
			default:
				UE_LOG(HTTPGameApiLog, Error, TEXT("Unknown response code: %d"), ResponseCode);
				break;
			}
		});

	FString RequestString;
	if(GetJsonStringFromStruct(UserInfoRequest, RequestString))
	{
		Request->SetURL(URL);
		Request->SetVerb(TEXT("Post"));
		Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
		Request->SetContentAsString(RequestString);
		Request->ProcessRequest();
	}
}


template <typename TStruct>
bool UHTTPGameAPIRequestsLib::GetJsonStringFromStruct(TStruct FilledStruct, FString& StringOutput)
{
	return FJsonObjectConverter::UStructToJsonObjectString(TStruct::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template <typename TStruct>
bool UHTTPGameAPIRequestsLib::GetStructFromJsonString(const FString& JsonString, TStruct& OutputStruct)
{
	return FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &OutputStruct, 0, 0);
}
