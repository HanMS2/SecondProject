// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NPC/NPCSellItemButtonWidget.h"
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

	virtual void NativeConstruct()override;
	UFUNCTION()
		void OnClickedButtonSell();

};
