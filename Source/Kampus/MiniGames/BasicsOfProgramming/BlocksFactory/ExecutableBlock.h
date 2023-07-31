// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockBase.h"
#include "ExecutableBlock.generated.h"



UCLASS()
class KAMPUS_API AExecutableBlock : public ABlockBase
{
	GENERATED_BODY()
public:
	AExecutableBlock();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
 