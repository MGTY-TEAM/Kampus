// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Libraries/Requests/GameServer/WSGameServerStructures.h"
#include "OtherPlayerActor.generated.h"

UCLASS()
class KAMPUS_API AOtherPlayerActor : public AActor
{
	GENERATED_BODY()

public:
	AOtherPlayerActor();

	void SetPlayerInfo(FPlayerInfo PlayerInfo);
	const FPlayerInfo& GetPlayerInfo() const;
private:
	FPlayerInfo M_PlayerInfo;
};
