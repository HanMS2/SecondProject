// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCDialogWidget.generated.h"

/**
 * 
 */




UCLASS()
class SECONDPROJECT_API UNPCDialogWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
		class UTextBlock* TextBlock_NPCName;
	UPROPERTY()
		class UTextBlock* TextBlock_Dialog;
	UPROPERTY()
		class UButton* Button_Chat;
	UPROPERTY()
		class UButton* Button_Buy;
	UPROPERTY()
		class UButton* Button_Sell;
	UPROPERTY()
		class UButton* Button_Close;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnClickedButtonChat();
	UFUNCTION()
		void OnClickedButtonBuy();
	UFUNCTION()
		void OnClickedButtonSell();
	UFUNCTION()
		void OnClickedButtonClose();


	UPROPERTY()
	class ANPCBase* ownerNPC;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UNPCSellItemWidget> sell_ItemWidgetClass;
	UPROPERTY()
		class UNPCSellItemWidget* sell_ItemWidget;

public:
	void Init(class ANPCBase* npc);

};
