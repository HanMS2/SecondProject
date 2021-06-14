// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemInformationWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/Component/InventoryComponent.h"

void UItemInformationWidget::init()
{
	TextBlock_ItemName->SetText(FText::GetEmpty());
	TextBlock_ItemType->SetText(FText::GetEmpty());
	TextBlock_ItemCount->SetText(FText::GetEmpty());
	TextBlock_ItemDescription->SetText(FText::GetEmpty());
	TextBlock_ItemDescription_Long->SetText(FText::GetEmpty());

}

void UItemInformationWidget::SetInformation(const FName& item_Code)
{
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	
	if (player != nullptr)
	{
		auto inventoryComp = player->GetinventoryComponent();
		if (inventoryComp != nullptr)
		{
			auto info = inventoryComp->GetItemInfo(item_Code);
			const auto item = inventoryComp->GetInventory()[item_Code];

			if (info != nullptr)
			{
				TextBlock_ItemName->SetText(FText::FromName(info->item_Name));
				TextBlock_ItemCount->SetText(FText::AsNumber(inventoryComp->GetItem(item_Code)->item_Count));
				TextBlock_ItemDescription->SetText(FText::FromName(info->item_Description));
				TextBlock_ItemDescription_Long->SetText(FText::FromName(info->item_Description_Long));
			}


			FString str = StaticEnum<EItemType>()->GetValueAsString(item->GetItemInfo()->item_Type);
			TextBlock_ItemType->SetText(FText::FromString(str));
			Image_ItemImage->SetBrushFromTexture(item->GetItemInfo()->item_Image);
		}
	}
}
