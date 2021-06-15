// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPC/NPCBuyItemButtonWidget.h"
#include "Components/Button.h"

void UNPCBuyItemButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Sell->OnClicked.AddUniqueDynamic(this, &UNPCBuyItemButtonWidget::OnClickedButtonSell);
}

void UNPCBuyItemButtonWidget::OnClickedButtonSell()
{
}
