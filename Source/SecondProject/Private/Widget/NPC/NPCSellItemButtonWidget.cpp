// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPC/NPCSellItemButtonWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Item/ItemActor.h"
#include "Character/NPC/NPCBase.h"

#include "Character/Player/PlayerCharacter.h"


void UNPCSellItemButtonWidget::SetInformation(const FNPCSellItem* info, class ANPCBase* owner)
{
	if (info != nullptr)
	{
		ownerNPC = owner;
		sellItemInfo = *info;
	}

	if (info->bInfinite)
	{
		TextBlock_ItemCount->SetText(FText::FromString("-"));
	}
	else
	{
		TextBlock_ItemCount->SetText(FText::AsNumber(info->count));
	}

	TextBlock_ItemPrice->SetText(FText::AsNumber(info->price));

	//GetDefaultObject 이거로 가져온 오브젝트는 에디터에 있는 오브젝트 본인이 수정되니 주의!.
	const auto item = info->sellItemClass.GetDefaultObject();
	const auto itemInfo = item->GetItemInformation<FItemInformation>();

	if (item != nullptr)
	{
		if (itemInfo != nullptr)
		{
			TextBlock_ItemName->SetText(FText::FromName(itemInfo->item_Name));
			Image_Item->SetBrushFromTexture(itemInfo->item_Image);
		}
	}
}

void UNPCSellItemButtonWidget::OnClickedButtonBuy()
{
	if (ownerNPC != nullptr)
	{
		const auto item = sellItemInfo.sellItemClass.GetDefaultObject();
		ownerNPC->OnChangeSaveItemCount.AddUniqueDynamic(this, &UNPCSellItemButtonWidget::OnChangedItemCount);
		ownerNPC->BuyItem(Cast<APlayerCharacter>(GetOwningPlayerPawn()),item->GetItemInformation<FItemInformation>()->item_Code);
	}

}

void UNPCSellItemButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button_Buy != nullptr)
	{
		Button_Buy->OnClicked.AddUniqueDynamic(this, &UNPCSellItemButtonWidget::OnClickedButtonBuy);
	}
}

void UNPCSellItemButtonWidget::OnChangedItemCount(const int32& newCount)
{
	TextBlock_ItemCount->SetText(FText::AsNumber(newCount));
}
