// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPC/NPCBuyItemButtonWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Character/Player/Component/InventoryComponent.h"
#include "Character/Player/PlayerCharacter.h"

void UNPCBuyItemButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Sell->OnClicked.AddUniqueDynamic(this, &UNPCBuyItemButtonWidget::OnClickedButtonSell);
}

void UNPCBuyItemButtonWidget::OnClickedButtonSell()
{
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	/*
	auto invenComp = player->GetinventoryComponent();

	if (invenComp != nullptr)
	{

	}
	*/

	if (ownerNPC != nullptr)
	{
		ownerNPC->OnChangeSellItemCount.AddUniqueDynamic(this, &UNPCBuyItemButtonWidget::UpdateItemCount);
		ownerNPC->SellItem(player, SellItemCode);
	}
}

void UNPCBuyItemButtonWidget::SetInformation(const FItemInformation* info, const int32& itemCount, ANPCBase* npc)
{
	ownerNPC = npc;
	SellItemCode = info->item_Code;
	TextBlock_ItemName->SetText(FText::FromName(info->item_Name));
	TextBlock_ItemCount->SetText(FText::AsNumber(itemCount));
	TextBlock_ItemPrice->SetText(FText::AsNumber(info->sellPrice));

	Image_Item->SetBrushFromTexture(info->item_Image);
}

void UNPCBuyItemButtonWidget::UpdateItemCount(const int32& count)
{
	if (count <= 0)
	{
		RemoveFromParent();
	}
	else
	{
		TextBlock_ItemCount->SetText(FText::AsNumber(count));
	}
}
