// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WebSockets/WebSocketGameClient.h"
#include "MultiplayerGameMode.generated.h"


class AOtherPlayerActor;
class UUserGameInstance;
/**
 * 
 */
UCLASS()
class KAMPUS_API AMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMultiplayerGameMode();
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;	

	
private:
	UFUNCTION()
	void OnConnectToGameServer();
	UFUNCTION()
	void OnPlayerInfosMessage(TArray<FPlayerInfo> PlayerInfos);

	UFUNCTION()
	void ClientTick();
	
	UWebSocketGameClient* M_WebSocketGameClient;
	UUserGameInstance* M_UserGameInstance;
	
	APawn* M_ControlledPawn;
	
	bool bUserRegistered;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AOtherPlayerActor> OtherPlayerActorClass;
	
	TArray<AOtherPlayerActor*> M_OtherPlayers;

	FTimerHandle ClientTickTimerHandle;
	
};
