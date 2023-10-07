// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportationPlane.generated.h"

UCLASS()
class KAMPUS_API ATeleportationPlane : public AActor
{
	GENERATED_BODY()
	
public:	

	ATeleportationPlane();

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* RobotPlane;
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* PlayerPlane;
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
