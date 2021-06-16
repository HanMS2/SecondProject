// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NPC/NPCSellItemButtonWidget.h"

#include "Item/ItemTypes.h"
#include "NPCBuyItemButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UNPCBuyItemButtonWidget : public UNPCSellItemButtonWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		class UButton* Button_Sell;
	UPROPERTY()
		FName SellItemCode;


	virtual void NativeConstruct()override;
	UFUNCTION()
		void OnClickedButtonSell();

public:

	void SetInformation(const FItemInformation* info, const int32& itemCount, class ANPCBase* npc);
	
	UFUNCTION()
		void UpdateItemCount(const int32& count);

};
