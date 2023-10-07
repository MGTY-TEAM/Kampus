// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreDrone/DefaultAnimDrone.h"
#include "UserInterface/ChatBox.h"
#include "DroneGuide.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EDroneGuide : uint8
{
	Drone_Idle UMETA(DisplayName = "Idle"),
	Drone_PlayerInteract UMETA(DisplayName = "PlayerInteract"),
	Drone_Talk UMETA(DisplayName = "Talk"),
	Drone_Loading UMETA(DisplayName = "Loading")
};

UCLASS()
class KAMPUS_API ADroneGuide : public ADefaultAnimDrone
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> BlueprintChatClass;
	UPROPERTY(EditDefaultsOnly,Category="Widget")
	UChatBox* ChatWidget;

protected:

	virtual void BeginPlay() override;
	
	virtual void Interact() override;
	virtual void EndInteract() override;
	void ChangeState(EDroneGuide State, float Duration = 0);

	virtual void StartIdleAnim() override;
	virtual void StopIdleAnim() override;
	virtual void StartRotateToPlayerAnim() override;
	virtual void StopRotateToPlayerAnim() override;

	void OpenChat();
	void CloseChat();
};
