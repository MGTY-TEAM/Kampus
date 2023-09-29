// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "EntryFormExecute.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFormExecute, const FString&, Token);
// This class does not need to be modified.
UINTERFACE()
class UEntryFormExecute : public UInterface
{
	GENERATED_BODY()
};

class KAMPUS_API IEntryFormExecute
{
	GENERATED_BODY()

public:
	FOnFormExecute OnFormExecute;
};
