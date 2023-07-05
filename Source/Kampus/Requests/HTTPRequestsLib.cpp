// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPRequestsLib.h"

#include "GenericPlatformHttp.h"
#include "HttpModule.h"
#include "IHttpResponse.h"
#include "JsonObject.h"
#include "JsonReader.h"
#include "JsonSerializer.h"
DEFINE_LOG_CATEGORY(LogRequests);

void UHTTPRequestsLib::AIMyLogicGetRequest(TFunction<void(const FString&)> CallBack, const FString& StringRequest)
{
	FHttpModule* Module = &FHttpModule::Get();
	auto Request = Module->CreateRequest();
	Request->OnProcessRequestComplete().BindLambda(
		[CallBack](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			FString YourJsonString = Response->GetContentAsString();
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(YourJsonString);
			if (FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField("data");
				FString Answer = DataObject->GetStringField("answer");
				CallBack(Answer);
			}
		});
	FString EncodedStringRequest = FGenericPlatformHttp::UrlEncode(StringRequest);
	FString URL = TEXT(
			"http://bot.jaicp.com/chatapi/WeapHmVI:3be9dbbc1eb926dd43ec452b0d54f3ebda7ff9de?clientId=test&query=")
		+ EncodedStringRequest;
	Request->SetURL(URL);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
	Request->ProcessRequest();
}

