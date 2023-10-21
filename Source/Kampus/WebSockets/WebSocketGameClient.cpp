// Fill out your copyright notice in the Description page of Project Settings.


#include "WebSocketGameClient.h"

#include "IWebSocket.h"
#include "Modules/ModuleManager.h"

#include "WebSocketsModule.h"
#include "Core/UserGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/Requests/GameServer/WSGameServerMethods.h"

UWebSocketGameClient::UWebSocketGameClient()
{
	FModuleManager::Get().LoadModule("WebSockets");
	M_WSModule = &FWebSocketsModule::Get();
}

void UWebSocketGameClient::Connect(const FString& Address)
{
#if WITH_WEBSOCKETS == 1
	if (M_WSModule)
	{
		M_WebSocketServer = M_WSModule->CreateWebSocket("ws://localhost:" + Address, "ws");
		if (M_WebSocketServer)
		{
			M_WebSocketServer->OnMessage().AddUObject(this, &UWebSocketGameClient::OnMessage);
			
			M_WebSocketServer->OnConnected().AddLambda([=]()
			{
				OnConnect.Broadcast();
			});
			
			M_WebSocketServer->Connect();
		}
	}
#endif
}

void UWebSocketGameClient::ReplicatePlayer(const FVector& pos, const FRotator& rot)
{
#if WITH_WEBSOCKETS == 1
	if (M_WebSocketServer)
	{
		if (M_WebSocketServer)
		{
			M_WebSocketServer->Send(UWSGameServerMethods::GetJsonStringByPlayerTransform(pos));
		}
	}
#endif
}

void UWebSocketGameClient::SetId(const FString& UserId)
{
#if WITH_WEBSOCKETS == 1
	if (M_WSModule)
	{
		if (M_WebSocketServer)
		{
			M_WebSocketServer->Send(UWSGameServerMethods::GetJsonStringByPlayerId(UserId));
		}
	}
#endif
}

void UWebSocketGameClient::Disconnect()
{
#if WITH_WEBSOCKETS == 1
	if (M_WSModule)
	{
		if (M_WebSocketServer)
		{
			M_WebSocketServer->Close();
		}
	}
#endif
}

void UWebSocketGameClient::OnMessage(const FString& Message)
{
#if WITH_WEBSOCKETS == 1
	/*UE_LOG(LogTemp, Warning, TEXT("WS Message: %s"), *Message);*/
	TArray<FPlayerInfo> PlayerInfos = UWSGameServerMethods::ParsePlayersInfo(Message);
	if (PlayerInfos.Num())
	{
		OnPlayerInfosMessage.Broadcast(PlayerInfos);
	}
#endif
}
