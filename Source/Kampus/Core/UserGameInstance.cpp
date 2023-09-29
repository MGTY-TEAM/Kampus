// Fill out your copyright notice in the Description page of Project Settings.


#include "UserGameInstance.h"

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

void UUserGameInstance::InitializeUserInfo()
{
	if (!M_UserToken.IsEmpty())
	{
			
	}
}
