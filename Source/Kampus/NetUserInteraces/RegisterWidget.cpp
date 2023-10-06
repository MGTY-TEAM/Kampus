// Fill out your copyright notice in the Description page of Project Settings.


#include "RegisterWidget.h"

#include "Button.h"
#include "EditableTextBox.h"
#include "FormFieldsValidatorLib.h"
#include "TextBlock.h"
#include "Requests/GameAPI/HTTPGameAPIRequestsLib.h"


void URegisterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	RegisterButton->OnClicked.AddDynamic(this, &URegisterWidget::OnRegisterButtonClicked);
}

void URegisterWidget::OnRegisterButtonClicked()
{
	//Clear Error Text
	ErrorText->SetText(FText());
	
	if (UFormFieldsValidatorLib::IsRegisterFieldsValid(LoginText->GetText(), NicknameText->GetText(),
	                                                   EmailText->GetText(), PasswordText->GetText(),
	                                                   ConfirmPasswordText->GetText()))
	{
		FRegisterRequest RegisterRequest;
		RegisterRequest.Login = GetStringValueFromEditableTextBox(LoginText);
		RegisterRequest.Nickname = GetStringValueFromEditableTextBox(NicknameText);
		RegisterRequest.Email = GetStringValueFromEditableTextBox(EmailText);
		RegisterRequest.Password = GetStringValueFromEditableTextBox(PasswordText);
		UHTTPGameAPIRequestsLib::GameAPIRegisterRequest([=](const bool bSuccess, const FRegisterResponse& RegisterResponse, const FRegisterErrorResponse& RegisterErrorResponse)
		{
			if (bSuccess)
			{
				UE_LOG(LogTemp, Warning, TEXT("Register success!"));
				OnFormExecute.Broadcast(RegisterResponse.Token);
			}
			else
			{
				ErrorText->SetText(FText::FromString(RegisterErrorResponse.Error));
			}
			
		},RegisterRequest);
	}
	else
	{
		ErrorText->SetText(FText::FromString("Invalid register fields!"));
	}
	
}

FString URegisterWidget::GetStringValueFromEditableTextBox(UEditableTextBox* EditableTextBox) const 
{
	FString StringValue = EditableTextBox->GetText().ToString();
	return StringValue;
}
