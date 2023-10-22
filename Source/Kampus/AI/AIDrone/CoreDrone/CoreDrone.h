// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIEntity.h"
#include "CoreDrone.generated.h"

/**
 * 
 */
UCLASS()
class KAMPUS_API ACoreDrone : public AAIEntity
{
	GENERATED_BODY()

public:
	ACoreDrone();
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Body;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Screen;
};
