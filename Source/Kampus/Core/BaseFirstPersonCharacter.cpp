// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFirstPersonCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ABaseFirstPersonCharacter::ABaseFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

// Called every frame
void ABaseFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("ForwardAxis",this, &ABaseFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RightAxis",this, &ABaseFirstPersonCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseX", this, &ABaseFirstPersonCharacter::LookRight);
	PlayerInputComponent->BindAxis("MouseY", this, &ABaseFirstPersonCharacter::LookUp);
}

