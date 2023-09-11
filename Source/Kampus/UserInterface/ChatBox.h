// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "ChatBox.generated.h"

/**
 * 
 */
UCLASS()
class KAMPUS_API UChatBox : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ParentPanel;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ChatBox_Panel;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* ChatBar_BG;
	UPROPERTY(meta = (BindWidget))
	class UImage* ChatIcon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Chat_BG;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* SendMessage_TextBox;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SendMessage_Button;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* Chat_ScrollBox;


protected:
	UFUNCTION()
	virtual bool Initialize();

	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SendMessageButtonClicked();

	UFUNCTION()
	void OnTextBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	
};
