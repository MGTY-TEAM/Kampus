// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameMode.h"

#include "OtherPlayerActor.h"
#include "TimerManager.h"
#include "Core/UserGameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/Requests/GameServer/WSGameServerStructures.h"
#include "WebSockets/WebSocketGameClient.h"


AMultiplayerGameMode::AMultiplayerGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	bUserRegistered = false;
}

void AMultiplayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	M_UserGameInstance= Cast<UUserGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (M_UserGameInstance)
	{
		M_WebSocketGameClient = NewObject<UWebSocketGameClient>(this);

		if (M_WebSocketGameClient)
		{
			M_WebSocketGameClient->Connect(M_UserGameInstance->GetGameServerPort());
			
			M_WebSocketGameClient->OnConnect.AddDynamic(this,&AMultiplayerGameMode::OnConnectToGameServer);
			M_WebSocketGameClient->OnPlayerInfosMessage.AddDynamic(this, &AMultiplayerGameMode::OnPlayerInfosMessage);
		}
	}
	M_ControlledPawn = UGameplayStatics::GetPlayerPawn(this,0);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(FInputModeGameOnly());

	GetWorldTimerManager().SetTimer(ClientTickTimerHandle, this, &AMultiplayerGameMode::ClientTick, 0.007, true);
}

void AMultiplayerGameMode::OnConnectToGameServer()
{
	UE_LOG(LogTemp, Warning, TEXT("MultiplayerGameMode: WS Connected"))
	if (M_WebSocketGameClient)
	{
		M_WebSocketGameClient->SetId(M_UserGameInstance->GetUserID());
		bUserRegistered = true;
	}
}

void AMultiplayerGameMode::OnPlayerInfosMessage(TArray<FPlayerInfo> PlayerInfos)
{
	for (FPlayerInfo PlayerInfo : PlayerInfos)
	{
		bool bContain = false;

		for (AOtherPlayerActor* OtherPlayerActor : M_OtherPlayers)
		{
			if (OtherPlayerActor->GetPlayerInfo().PlayerID == PlayerInfo.PlayerID)
			{
				OtherPlayerActor->SetPlayerInfo(PlayerInfo);
				bContain = true;
				break;
			}
		}
		if (!bContain)
		{
			AOtherPlayerActor* OtherPlayerActor = GetWorld()->SpawnActor<AOtherPlayerActor>(OtherPlayerActorClass);
			if (OtherPlayerActor)
			{
				OtherPlayerActor->SetPlayerInfo(PlayerInfo);
				M_OtherPlayers.Add(OtherPlayerActor);
			}
		}
	}
}

void AMultiplayerGameMode::ClientTick()
{
	if (M_WebSocketGameClient && M_ControlledPawn)
	{
		if (bUserRegistered)
		{
			if (M_ControlledPawn->GetVelocity().Size() > 0)
			{
				M_WebSocketGameClient->ReplicatePlayer(M_ControlledPawn->GetActorLocation(), M_ControlledPawn->GetActorRotation());
			}
		} 
	}
}

void AMultiplayerGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (M_WebSocketGameClient)
	{
		M_WebSocketGameClient->Disconnect();
	}
	
}

void AMultiplayerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
