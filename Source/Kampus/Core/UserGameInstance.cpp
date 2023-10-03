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

void UUserGameInstance::TryToGetUserInfo()
{
	FUserInfoRequest UserInfoRequest;
	UserInfoRequest.Token = M_UserToken;
	UHTTPGameAPIRequestsLib::GameAPIUserInfoRequest(
		[](const bool& success, const FUserInfoResponse& UserInfoResponse, const FUserInfoErrorResponse& UserInfoErrorResponse)
		{
			fjfjkj;
		}, UserInfoRequest);
}

void UUserGameInstance::InitializeUserInfo()
{
	if (!M_UserToken.IsEmpty())
	{
	}
}
