// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EquipmentItemListWidget.h"

#include "Character/Player/Component/InventoryComponent.h"
#include "Widget/DragItemButtonWidget.h"
#include "Components/ScrollBox.h"
#include "Character/Player/PlayerCharacter.h"

void UEquipmentItemListWidget::OnClickedButtonItem()
{

}
void UEquipmentItemListWidget::OnClickedButtonAll()
{
	init();
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();

		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{

			auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

			if (button != nullptr)
			{
				button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
				ScrollBox_ItemList->AddChild(button);
			}
		}
	}
}
void UEquipmentItemListWidget::OnClickedButtonWeapon()
{
	init();

	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Weapon)
				{

					auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

					if (button != nullptr)
					{
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}

}
void UEquipmentItemListWidget::OnClickedButtonSheild()
{

	init();

	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Shield)
				{

					auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

					if (button != nullptr)
					{
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}

}
void UEquipmentItemListWidget::OnClickedButtonChest()
{
	init();

	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Chest)
				{

					auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

					if (button != nullptr)
					{
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}


}
void UEquipmentItemListWidget::OnClickedButtonGlove()
{
	init();

	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Gloves)
				{

					auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

					if (button != nullptr)
					{
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
}
void UEquipmentItemListWidget::OnClickedButtonLeg()
{
	init();


	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Legs)
				{

					auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

					if (button != nullptr)
					{
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
}
void UEquipmentItemListWidget::OnClickedButtonBoots()
{
	init();

	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Boots)
				{

					auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

					if (button != nullptr)
					{
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}


}
void UEquipmentItemListWidget::OnClickedButtonHelmet()
{
	init();

	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Helmet)
				{

					auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

					if (button != nullptr)
					{
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}


}
void UEquipmentItemListWidget::OnClickedButtonConsume()
{
	init();

	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Consume)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr)
				{

					auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

					if (button != nullptr)
					{
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
}
void UEquipmentItemListWidget::UpdateItemList(class UInventoryComponent* invenComp)
{
	init();


	if (invenComp != nullptr && dragItemButtonWidgetclass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{

			auto button = CreateWidget<UDragItemButtonWidget>(GetOwningPlayer(), dragItemButtonWidgetclass.Get());

			if (button != nullptr)
			{
				button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
				ScrollBox_ItemList->AddChild(button);
			}
		}
	}
}