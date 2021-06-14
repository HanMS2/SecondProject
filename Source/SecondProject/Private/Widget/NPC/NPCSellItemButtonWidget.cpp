// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPC/NPCSellItemButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Item/ItemActor.h"

void UNPCSellItemButtonWidget::SetInformation(const FNPCSellItem* info)
{
	if (info->bInfinite)
	{
		TextBlock_ItemCount->SetText(FText::FromString("-"));

	}
	else
	{
		TextBlock_ItemCount->SetText(FText::AsNumber(info->count));
	}

	TextBlock_ItemPrice->SetText(FText::AsNumber(info->price));

	//GetDefaultObject �̰ŷ� ������ ������Ʈ�� �����Ϳ� �ִ� ������Ʈ ������ �����Ǵ� ����!.
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
}

void UNPCSellItemButtonWidget::NativeConstruct()
{
	//Super::NativeConstruct();
}
