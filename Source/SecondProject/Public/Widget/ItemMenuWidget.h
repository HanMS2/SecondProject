// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UItemMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UButton* Button_Use;
	UPROPERTY()
		class UButton* Button_Remve;
	UPROPERTY()
		class UButton* Button_Drop;
	UPROPERTY()
		class UButton* Button_Cancle;

	UFUNCTION()
		void OnClickedButtonUse();
	UFUNCTION()
		void OnClickedButtonDrop();
	UFUNCTION()
		void OnClickedButtonRemove();
	UFUNCTION()
		void OnClickedButtonCancle();

	virtual void NativeConstruct() override;

	FName itemCode;
public:
	void SetItemCode(const FName& code) { itemCode = code; }
	
	void DisableUseButton();
	void EnableUseButton();

};
