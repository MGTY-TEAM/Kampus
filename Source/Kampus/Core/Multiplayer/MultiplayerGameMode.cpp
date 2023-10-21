// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameMode.h"

#include "Core/UserGameInstance.h"
#include "Kismet/GameplayStatics.h"
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
	for ()
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
	
	if (M_WebSocketGameClient && M_ControlledPawn)
	{
		if (bUserRegistered)
		{
			M_WebSocketGameClient->ReplicatePlayer(M_ControlledPawn->GetActorLocation(), M_ControlledPawn->GetActorRotation());
		} 
	}
}
