// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Character/NPC/NPCBase.h"

#include "NPCSellItemButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UNPCSellItemButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UButton* Button_Buy;
	UPROPERTY()
		class UImage* Image_Item;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemCount;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemPrice;
	
public:
	void SetInformation(const FNPCSellItem* info);

	UFUNCTION()
		void OnClickedButtonBuy();
	virtual void NativeConstruct()override;

};
