// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicsOfProgrammingGameMode.h"

#include "UserWidget.h"


// Sets default values
ABasicsOfProgrammingGameMode::ABasicsOfProgrammingGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasicsOfProgrammingGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (StartupWidget)
	{
		UUserWidget* StartupWidgetInstance = CreateWidget(GetWorld(), StartupWidget);
		if (StartupWidgetInstance)
		{
			StartupWidgetInstance->AddToViewport();
		}
	}
}

// Called every frame
void ABasicsOfProgrammingGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

