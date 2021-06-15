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
	UPROPERTY()
		struct FNPCSellItem sellItemInfo;
	UPROPERTY()
		class ANPCBase* ownerNPC;
public:
	void SetInformation(const FNPCSellItem* info, class ANPCBase* owner);

	UFUNCTION()
		void OnClickedButtonBuy();
	virtual void NativeConstruct()override;

	UFUNCTION()
		void OnChangedItemCount(const int32& newCount);

};
