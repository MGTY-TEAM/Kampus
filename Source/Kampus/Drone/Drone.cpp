// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Core/BaseFirstPersonCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"


ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true;
	Robot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Robot"));
	Face = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face"));
	Face->SetupAttachment(Robot);
	
}

void ADrone::Interact()
{
	bCanInteract = true;
	UE_LOG(LogTemp, Warning, TEXT("Interaction"));
}

void ADrone::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ABaseFirstPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanInteract)
	{
		FVector StartLocation = this->GetCapsuleComponent()->GetComponentLocation(); // Начальная позиция
		FVector TargetLocation = PlayerCharacter->GetActorLocation(); // Позиция цели
	
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);
	
		FRotator StartRotation = this->GetCapsuleComponent()->GetComponentRotation();
		FRotator EndRotation = LookAtRotation;
		float InterpolationFactor = 0.5f; // Фактор интерполяции от 0.0 до 1.0

		FRotator InterpolatedRotation = FMath::Lerp(StartRotation, EndRotation, InterpolationFactor);
		this->GetCapsuleComponent()->SetWorldRotation(LookAtRotation);
	}
}

void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

