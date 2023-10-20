// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPAiMyLogicRequestsLib.h"

#include "GenericPlatformHttp.h"
#include "HttpModule.h"
#include "IHttpResponse.h"
#include "JsonObject.h"
#include "JsonReader.h"
#include "JsonSerializer.h"
DEFINE_LOG_CATEGORY(LogRequests);

void UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest(TFunction<void(const FString&)> CallBack, const FString& StringRequest, const FString& URL)
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
	FString FULL_URL = URL + "&query=" + EncodedStringRequest;
	Request->SetURL(FULL_URL);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
	Request->ProcessRequest();
}

