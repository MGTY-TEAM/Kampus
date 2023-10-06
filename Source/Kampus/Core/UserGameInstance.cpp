// Fill out your copyright notice in the Description page of Project Settings.


#include "UserGameInstance.h"

#include "Requests/GameAPI/HTTPGameAPIRequestsLib.h"

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
		[this](const bool& bSuccess, const FUserInfoResponse& UserInfoResponse, const FUserInfoErrorResponse& UserInfoErrorResponse)
		{
			if (bSuccess)
			{
				M_UserInfo.Email = UserInfoResponse.Email;
				M_UserInfo.Nickname = UserInfoResponse.Nickname;
				return true;
			}
			return false;
		}, UserInfoRequest);
	
	return false;
}

void UUserGameInstance::InitializeUserInfo()
{
	if (!M_UserToken.IsEmpty())
	{
	}
}
