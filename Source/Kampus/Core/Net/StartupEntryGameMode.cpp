// Fill out your copyright notice in the Description page of Project Settings.


#include "StartupEntryGameMode.h"

#include "UserWidget.h"

#include "Core/UserGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "NetUserInteraces/EntryWidget.h"

AStartupEntryGameMode::AStartupEntryGameMode()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AStartupEntryGameMode::BeginPlay()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	
	M_EntryWidget = CreateWidget<UEntryWidget>(GetWorld(), EntryWidgetClass);
	M_EntryWidget->AddToViewport();
	
	M_EntryWidget->OnEntryExecute.AddDynamic(this, &AStartupEntryGameMode::OnEntryWidgetExecute);
	
	Super::BeginPlay();
}

void AStartupEntryGameMode::OnEntryWidgetExecute(const FString& Token)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Entry")));
	if (!Token.IsEmpty())
	{
		UUserGameInstance* UserGameInstance =  Cast<UUserGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (UserGameInstance)
		{
			UserGameInstance->SetUserToken(Token);
			UE_LOG(LogTemp, Warning, TEXT("Entry is finished!"));
		}
		M_EntryWidget->RemoveFromParent();
	}
	
}
