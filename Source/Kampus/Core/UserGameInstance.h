// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UserGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, Category = "User") FString Nickname;
	UPROPERTY(BlueprintReadOnly, Category = "User") FString Email;
	UPROPERTY(BlueprintReadOnly, Category = "User") FString ID;
	
};

UCLASS()
class KAMPUS_API UUserGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	/**
	 * @brief Get user info.
	 * @return FUserInfo struct which containing user info.
	 */
	const FUserInfo& GetUserInfo() const;

	void SetUserToken(const FString& Token);
	const FString& GetUserToken() const;

	/**
	 * @brief Try to get user info from api request.
	 * @return true if user info filled up UserInfo, otherwise false;
	 */
	bool TryToGetAndFillUserInfo();
	
	void TryConnectToGameServer(const FString& Port);

protected:
	virtual void Init() override;
private:
	FUserInfo M_UserInfo;
	FString M_UserToken;

	FString GameServerPort;
};
