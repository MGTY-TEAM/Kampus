// Fill out your copyright notice in the Description page of Project Settings.


#include "WSGameServerMethods.h"
#include "WSGameServerStructures.h"
#include "Json.h"

FString UWSGameServerMethods::GetJsonStringByPlayerTransform(FVector UserPosition)
{
	FString JsonString = "{ \"event\" : \"update-position\", \"position\" : { \"x\" : \""+ FString::SanitizeFloat(UserPosition.X) +
		"\", \"y\" : \""+ FString::SanitizeFloat(UserPosition.Y) +"\",  \"z\" : \"" +
			FString::SanitizeFloat(UserPosition.Z) +"\"}}";
	
	return JsonString;
}

FString UWSGameServerMethods::GetJsonStringByPlayerId(const FString& PlayerId)
{
	FString JsonString = "{ \"event\" : \"set-id\", \"id\" : \"" + PlayerId + "\"}";
	return JsonString;
}

TArray<FPlayerInfo> UWSGameServerMethods::ParsePlayersInfo(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		FString Event = JsonObject->GetStringField("event");
		if (Event == "player-positions")
		{
			TArray<FPlayerInfo> PlayerInfos;
			
			TArray<TSharedPtr<FJsonValue>> DataArray = JsonObject->GetArrayField("data");
			FString ResultString;

			for (TSharedPtr<FJsonValue> DataValue : DataArray)
			{
				FPlayerInfo PlayerInfo;
				TSharedPtr<FJsonObject> DataObject = DataValue->AsObject();
				
				FString UserId = DataObject->GetStringField("userId");
				
				PlayerInfo.PlayerID = UserId;
				
				TSharedPtr<FJsonObject> PositionObject = DataObject->GetObjectField("position");
				FString X = PositionObject->GetStringField("x");
				FString Y = PositionObject->GetStringField("y");
				FString Z = PositionObject->GetStringField("z");
				
				PlayerInfo.Position = FVector(FCString::Atof(*X),FCString::Atof(*Y),FCString::Atof(*Z));
				PlayerInfos.Add(PlayerInfo);
			}
			return PlayerInfos;
		}
	}
	return TArray<FPlayerInfo>();
}
