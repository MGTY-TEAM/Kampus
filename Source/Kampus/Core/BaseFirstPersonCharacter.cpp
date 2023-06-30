// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFirstPersonCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "TokenizedMessage.h"
#include "Engine/Engine.h"
#include "Entity/Interactable/InteractableActor.h"

ABaseFirstPersonCharacter::ABaseFirstPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ABaseFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseFirstPersonCharacter::Interact()
{
	FVector Start = CameraComponent->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector End = ((ForwardVector * InteractionDistance) + Start);

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			IInteractable* InteractableObject = Cast<IInteractable>(OutHit.Actor);
			if (InteractableObject)
			{
				InteractableObject->Interact();
			}
		}
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5, 0, 1);
}


void ABaseFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ABaseFirstPersonCharacter::Interact);

	PlayerInputComponent->BindAxis("ForwardAxis", this, &ABaseFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RightAxis", this, &ABaseFirstPersonCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseX", this, &ABaseFirstPersonCharacter::LookRight);
	PlayerInputComponent->BindAxis("MouseY", this, &ABaseFirstPersonCharacter::LookUp);
}


void ABaseFirstPersonCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * Speed * value);
}

void ABaseFirstPersonCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * Speed * value);
}

void ABaseFirstPersonCharacter::LookUp(float value)
{
	AddControllerPitchInput(value * MouseSpeed * -1);
}

void ABaseFirstPersonCharacter::LookRight(float value)
{
	AddControllerYawInput(value * MouseSpeed);
}

void ABaseFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
