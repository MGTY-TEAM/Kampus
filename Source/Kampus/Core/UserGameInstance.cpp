// Fill out your copyright notice in the Description page of Project Settings.


#include "UserGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Libraries/Requests/GameAPI/HTTPGameAPIRequestsLib.h"
#include "Libraries/Requests/GameAPI/HTTPGameAPIStructures.h"


const FUserInfo& UUserGameInstance::GetUserInfo() const
{
	return M_UserInfo;
}

void UUserGameInstance::SetUserToken(const FString& Token)
{
	if (M_UserToken.IsEmpty())
	{
		M_UserToken = Token;
	}
}

const FString& UUserGameInstance::GetUserToken() const
{
	return M_UserToken;
}

bool UUserGameInstance::TryToGetAndFillUserInfo()
{
	FUserInfoRequest UserInfoRequest;
	UserInfoRequest.Token = GetUserToken();

	UHTTPGameAPIRequestsLib::GameAPIUserInfoRequest(
		[this](const bool& bSuccess, const FUserInfoResponse& UserInfoResponse, const FErrorResponse& UserInfoErrorResponse)
		{
			if (bSuccess)
			{
				M_UserInfo.Email = UserInfoResponse.Email;
				M_UserInfo.Nickname = UserInfoResponse.Nickname;
				M_UserInfo.ID = UserInfoResponse.ID;
				UE_LOG(LogTemp, Warning, TEXT("User info is filled. UserID: %s"), *UserInfoResponse.ID);			
				return true;
			}
			return false;
		}, UserInfoRequest);
	
	return false;
}

void UUserGameInstance::TryConnectToGameServer(const FString& Port)
{
	if (!Port.IsEmpty())
	{
		GameServerPort = Port;
		UGameplayStatics::OpenLevel(this, "");	
	}
}



void UUserGameInstance::Init()
{
	Super::Init();
}
