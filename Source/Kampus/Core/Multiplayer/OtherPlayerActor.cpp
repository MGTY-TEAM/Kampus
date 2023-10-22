// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherPlayerActor.h"



const FPlayerInfo& AOtherPlayerActor::GetPlayerInfo() const
{
	return M_PlayerInfo;
}

AOtherPlayerActor::AOtherPlayerActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AOtherPlayerActor::SetPlayerInfo(FPlayerInfo PlayerInfo)
{
	M_PlayerInfo = PlayerInfo;
	SetActorLocation(PlayerInfo.Position); 
}



