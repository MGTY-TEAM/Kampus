// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Requests/GameServer/WSGameServerStructures.h"
#include "Object.h"
#include "WebSocketGameClient.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInfosMessage, TArray<FPlayerInfo>, PlayerInfos);

class IWebSocket;
class FWebSocketsModule;
/**
 * 
 */
UCLASS()
class KAMPUS_API UWebSocketGameClient : public UObject
{
	GENERATED_BODY()

public:
	UWebSocketGameClient();

	FOnConnect OnConnect;
	FOnPlayerInfosMessage OnPlayerInfosMessage;
	
	void Connect(const FString& Address);
	void Disconnect();
	void ReplicatePlayer(const FVector& pos, const FRotator& rot);
	
	void SetId(const FString& UserId);

private:
	TSharedPtr<IWebSocket> M_WebSocketServer;

	FWebSocketsModule* M_WSModule;

	UFUNCTION()
	void OnMessage(const FString& Message);
};
