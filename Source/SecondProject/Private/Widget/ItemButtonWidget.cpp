// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Character/Player/Controller/CustomController.h"
#include "Widget/ItemInformationWidget.h"
#include "Item/ItemActor.h"
#include "Character/Player/Component/InventoryComponent.h"

#include "Character/Player/PlayerCharacter.h"
#include "Widget/ItemMenuWidget.h"
#include "Widget/ToolTipWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Widget/ItemListWidget.h"

void UItemButtonWidget::SetInformation(const FItemInformation* info, const int32& item_Count)
{
	item_Code = info->item_Code;

	TextBlock_ItemName->SetText(FText::FromName(info->item_Name));
	TextBlock_ItemCount->SetText(FText::AsNumber(item_Count));
	TextBlock_Description->SetText(FText::FromName(info->item_Description));
	
	Image_ItemImage->SetBrushFromTexture(info->item_Image);

}

void UItemButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Item->OnHovered.AddUniqueDynamic(this, &UItemButtonWidget::OnHoveredButtonItem);
	Button_Item->OnClicked.AddUniqueDynamic(this, &UItemButtonWidget::OnClickedButtonItem);

	if (toolTipWidgetClass != nullptr)
	{
		MytoolTipWidget = CreateWidget<UToolTipWidget>(GetOwningPlayer(), toolTipWidgetClass.Get());
		if (MytoolTipWidget != nullptr)
		{
			SetToolTip(MytoolTipWidget);
		
		}
	}
}

void UItemButtonWidget::OnHoveredButtonItem()
{

	auto contoroller = Cast<ACustomController>(GetOwningPlayer());

	if (contoroller != nullptr)
	{
		auto infoWidget = contoroller->GetItemInformationWidget();
		if (infoWidget != nullptr)
		{
			infoWidget->SetInformation(item_Code);

		}
	}

	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player != nullptr)
	{
		auto invenComp = player->GetinventoryComponent();
		if (invenComp != nullptr)
		{
			auto inven = invenComp->GetItemInfo(item_Code);
			if (inven != nullptr)
			{
				MytoolTipWidget->SetText(inven->item_Description);
			}
		}
	}
}

void UItemButtonWidget::OnClickedButtonItem()
{
	if (UMG_ItemList != nullptr)
	{
		UMG_ItemList->ShowItemMenu(item_Code);
	}
	/*
	if (itemMenuWidgetClass != nullptr)
	{
		if (itemMenuWidget == nullptr)
		{
			itemMenuWidget = CreateWidget<UItemMenuWidget>(GetOwningPlayer(), itemMenuWidgetClass.Get());
		}
		itemMenuWidget->SetItemCode(item_Code);
		
		auto mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer());

		itemMenuWidget->SetPositionInViewport(mousePos, false);

		if (itemMenuWidget->IsInViewport() == false)
		{
			itemMenuWidget->AddToViewport();
		}

		//Cast<APlayerCharacter>(GetOwningPlayerPawn())
		//	->GetinventoryComponent()->UseItem(item_Code, GetOwningPlayerPawn());

	}
	
	*/
}

void UItemButtonWidget::UpdateItemCount(const int32& item_Count)
{
	TextBlock_ItemCount->SetText(FText::AsNumber(item_Count));
}

void UItemButtonWidget::SetItemListWidget(UItemListWidget* p_widget)
{
	UMG_ItemList = p_widget;
}
