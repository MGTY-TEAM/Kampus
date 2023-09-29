// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"

#include "Button.h"
#include "EditableTextBox.h"
#include "FormFieldsValidatorLib.h"
#include "Engine/Engine.h"
#include "Requests/GameAPI/HTTPGameAPIRequestsLib.h"

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
		UHTTPGameAPIRequestsLib::GameAPILoginRequest([=](const bool& bSuccess, const FLoginResponse& LoginResponse, const FLoginErrorResponse&)
		{
			if (bSuccess)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Success login")));
				UE_LOG(LogTemp, Warning, TEXT("Token: %s"), *LoginResponse.Token);
				OnFormExecute.Broadcast(LoginResponse.Token);
			}
		},LoginRequest);
	}
}

FString ULoginWidget::GetStringValueFromEditableTextBox(UEditableTextBox* EditableTextBox) const
{
	FString StringValue = EditableTextBox->GetText().ToString();
	return StringValue;
}
