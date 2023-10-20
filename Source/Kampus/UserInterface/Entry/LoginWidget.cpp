// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"

#include "Button.h"
#include "EditableTextBox.h"

#include "TextBlock.h"
#include "Engine/Engine.h"
#include "Libraries/Requests/GameAPI/HTTPGameAPIRequestsLib.h"
#include "Libraries/Requests/GameAPI/HTTPGameAPIStructures.h"
#include "Libraries/Validation/FormFieldsValidatorLib.h"

void ULoginWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	LoginButton->OnClicked.AddDynamic(this, &ULoginWidget::OnLoginButtonClicked);
}

void ULoginWidget::OnLoginButtonClicked()
{
	if (UFormFieldsValidatorLib::IsLoginFieldsValid(LoginText->GetText(), PasswordText->GetText()))
	{
		FLoginRequest LoginRequest;
		LoginRequest.Login =  GetStringValueFromEditableTextBox(LoginText);
		LoginRequest.Password = GetStringValueFromEditableTextBox(PasswordText);
		UHTTPGameAPIRequestsLib::GameAPILoginRequest([=](const bool& bSuccess, const FLoginResponse& LoginResponse, const FErrorResponse& LoginErrorResponse)
		{
			if (bSuccess)
			{
				UE_LOG(LogTemp, Warning, TEXT("Token: %s"), *LoginResponse.Token);
				OnFormExecute.Broadcast(LoginResponse.Token);
			}
			else
			{
				ErrorText->SetText(FText::FromString(LoginErrorResponse.Error));
			}
		},LoginRequest);
	}
	else
	{
		ErrorText->SetText(FText::FromString("Invalid login fields!"));
	}
}

FString ULoginWidget::GetStringValueFromEditableTextBox(UEditableTextBox* EditableTextBox) const
{
	FString StringValue = EditableTextBox->GetText().ToString();
	return StringValue;
}
