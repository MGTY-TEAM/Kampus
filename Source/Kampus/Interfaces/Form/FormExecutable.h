// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "FormExecutable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFormExecute, const FString&, Token);
// This class does not need to be modified.
UINTERFACE()
class UFormExecutable : public UInterface
{
	GENERATED_BODY()
};

class KAMPUS_API IFormExecutable
{
	GENERATED_BODY()

public:
	FOnFormExecute OnFormExecute;
};
