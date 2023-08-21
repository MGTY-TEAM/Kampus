// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Button.h"
#include "CodeBaseWidget.h"
#include "ComboBoxString.h"

#include "Blueprint/UserWidget.h"
#include "Interfaces/CodeEntity.h"
#include "CodeListing.generated.h"

class UVerticalBox;
/**
 * 
 */
UCLASS()
class KAMPUS_API UCodeListing : public UCodeBaseWidget, public ICodeEntity
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalCodeListing;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* AddEntitySelector;

	TMap<FString, TSubclassOf<UCodeBaseWidget>> OptionToEntityMap;

	TMap<ICodeEntity*, UCodeBaseWidget*> GetCodeEntities();

	UPROPERTY(EditDefaultsOnly, Category="UIClasses")
	TSubclassOf<UCodeBaseWidget> ActionWidget;
	UPROPERTY(EditDefaultsOnly, Category="UIClasses")
	TSubclassOf<UCodeBaseWidget> IfWidget;
	UPROPERTY(EditDefaultsOnly, Category="UIClasses")
	TSubclassOf<UCodeBaseWidget> WhileWidget;


	UFUNCTION()
	void AddSelectorOnChanged(FString SelectedString, ESelectInfo::Type SelectionType);

	TArray<UCodeBaseWidget*> GetEntities();
protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveCall(UCodeBaseWidget* ChildEntity);
	virtual void RemoveCall_Implementation(UCodeBaseWidget* ChildEntity) override;

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;


private:
	TMap<ICodeEntity*, UCodeBaseWidget*> CodeEntities;
};
