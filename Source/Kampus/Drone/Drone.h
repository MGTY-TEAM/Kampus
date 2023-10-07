// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotStates.h"
#include "TeleportationPlane.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interaction/Interactable.h"


#include "Drone.generated.h"


class UChatBox;

class ABaseFirstPersonCharacter;

UCLASS()
class KAMPUS_API ADrone : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADrone();
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* Robot;
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* Face;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin")
	float Frecuency1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin")
	float Amplitude1;

	ERobotStates CurrentState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="KeyWords")
	TArray<FString> KeyWordsForTeleportation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="KeyWords")
	TArray<FString> KeyWordsPlaces;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="KeyWords")
	FString BotURL;
	UPROPERTY(EditAnywhere, Category="KeyWords")
	TArray<AActor*> TeleportationPlaces;
	UPROPERTY(EditDefaultsOnly, Category="KeyWords")
	ATeleportationPlane* TeleportationPlace;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> BlueprintChatClass;
	UPROPERTY(EditDefaultsOnly,Category="Widget")
	UChatBox* ChatWidget;
	
	UPROPERTY(EditDefaultsOnly,Category="Character")
	ABaseFirstPersonCharacter* PlayerCharacter;

	FTimerHandle IdleAnim_Timer;
	FTimerHandle RotateToPlayer_Timer;

	UFUNCTION()
	void TeleportToLocation(int index);

	virtual void Interact() override;
	virtual void EndInteract() override;
	void ChangeState(ERobotStates State, float Duration = 0);

	void IdleAnim();
	void RotateToPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
