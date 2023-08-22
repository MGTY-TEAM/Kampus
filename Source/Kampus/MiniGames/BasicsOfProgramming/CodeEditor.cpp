// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeEditor.h"

#include "ActionVisual.h"
#include "Button.h"
#include "CodeListing.h"
#include "ControlledRobot.h"
#include "IfVisual.h"
#include "Engine/Engine.h"
#include "Interfaces/Action.h"
#include "Interfaces/IF.h"
#include "Kismet/GameplayStatics.h"
#

class UActionVisual;

void UCodeEditor::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	RunButton->OnClicked.AddDynamic(this, &UCodeEditor::RunButtonOnClick);
	AActor* FoundedActor = UGameplayStatics::GetActorOfClass(GetWorld(), AControlledRobot::StaticClass());
	if (FoundedActor)
	{
		ControlledRobot = Cast<AControlledRobot>(FoundedActor);
		if (ControlledRobot)
		{
#if WITH_EDITOR
			UE_LOG(LogTemp, Warning, TEXT("Controlled Robot succesfuly attached to code editor"))
#endif
			
		}
	}
	else
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("Controlled Robot not finded"))
#endif
	}
}


void UCodeEditor::RunButtonOnClick()
{
	#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Start Running Code"))
	#endif
	ParseCode(MainCodeListing);
}

void UCodeEditor::ParseCode(UCodeListing* CodeListing)
{
	TArray<UCodeBaseWidget*> CodeWidgets = CodeListing->GetEntities();
	if (CodeWidgets.Num())
	{
		for (auto CodeWidget : CodeWidgets)
		{
			if (CodeWidget)
			{

				UActionVisual* Action = Cast<UActionVisual>(CodeWidget);
				if (Action)
				{
#if WITH_EDITOR
					UE_LOG(LogTemp, Warning, TEXT("Parser: Action (%s)"), *Action->GetName());
#endif
					if (ControlledRobot)
					{
						switch (Action->Action)
						{
						case (EActions::EA_MOVE):
							{
								ControlledRobot->Move();
								break;
							}
						case (EActions::EA_ROTATE_RIGHT):
							{
								ControlledRobot->RotateRight();
								break;
							}
						case (EActions::EA_ROTATE_LEFT):
							{
								ControlledRobot->RotateLeft();
								break;
							}
						}
					}

				}
				UIfVisual* If = Cast<UIfVisual>(CodeWidget);
				if (If)
				{
#if WITH_EDITOR	
					UE_LOG(LogTemp, Warning, TEXT("Parser: If (%s)"), *If->GetName());
#endif
					if (ControlledRobot)
					{
						bool bCondition;
						switch (If->Condition)
						{
						case (EConditions::EFC_WALL_FORWARD):
							{
								bCondition = ControlledRobot->IsWallForward();
								break;
							}
						case (EConditions::EFC_WALL_RIGHT):
							{
								bCondition = ControlledRobot->IsWallRight();
								break;
							}
						case (EConditions::EFC_WALL_LEFT):
							{
								bCondition = ControlledRobot->IsWallLeft();
								break;
							}
						}
						if (bCondition)
						{
							ParseCode(If->TrueCodeListing);
						}
					}
				}
			}

		}
	}
}
