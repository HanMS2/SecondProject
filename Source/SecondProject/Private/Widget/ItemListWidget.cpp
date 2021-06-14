// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemListWidget.h"
#include "Components/ScrollBox.h"
#include "Character/Player/Component/InventoryComponent.h"
#include "Widget/ItemButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Widget/ItemMenuWidget.h"
#include "Character/Player/PlayerCharacter.h"

void UItemListWidget::init()
{
	ScrollBox_ItemList->ClearChildren();

}

void UItemListWidget::UpdateItemList(UInventoryComponent* invenComp)
{
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{

			auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());
		
			if (button != nullptr)
			{
				button->SetItemListWidget(this);
				button->SetInformation(iter->Value->GetItemInfo(),iter->Value->item_Count);
				ScrollBox_ItemList->AddChild(button);
			}
		}
	}
}

void UItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Button_All->OnClicked.AddUniqueDynamic(this, &UItemButtonWidget::OnClickedButtonItem);
	
	Button_All->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedButtonAll);
	Button_Weapon->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedButtonWeapon);
	Button_Shield->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedButtonSheild);
	Button_Chest->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedButtonChest);
	Button_Leg->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedButtonLeg);
	Button_Helmet->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedButtonHelmet);
	Button_Boots->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedButtonBoots);
	Button_Glove->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedButtonGlove);
	Button_Consume->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedButtonConsume);

}

void UItemListWidget::OnClickedButtonItem()
{

}

void UItemListWidget::OnClickedButtonAll()
{
	init();
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();

		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{

			auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());

			if (button != nullptr)
			{
				button->SetItemListWidget(this);
				button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
				ScrollBox_ItemList->AddChild(button);
			}
		}
	}

}

void UItemListWidget::OnClickedButtonWeapon()
{
	init();
	
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Weapon)
				{

					auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());

					if (button != nullptr)
					{
						button->SetItemListWidget(this);
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
	
}

void UItemListWidget::OnClickedButtonSheild()
{
	init();
	
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Shield)
				{

					auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());

					if (button != nullptr)
					{
						button->SetItemListWidget(this);
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
	
}

void UItemListWidget::OnClickedButtonChest()
{
	init();
	
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Chest)
				{

					auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());

					if (button != nullptr)
					{
						button->SetItemListWidget(this);
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
	
}

void UItemListWidget::OnClickedButtonGlove()
{
	init();
	
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Gloves)
				{

					auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());

					if (button != nullptr)
					{
						button->SetItemListWidget(this);
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
	
}

void UItemListWidget::OnClickedButtonLeg()
{
	init();

	
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Legs)
				{

					auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());

					if (button != nullptr)
					{
						button->SetItemListWidget(this);
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
	
}

void UItemListWidget::OnClickedButtonBoots()
{
	init();
	
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Boots)
				{

					auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());

					if (button != nullptr)
					{
						button->SetItemListWidget(this);
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
	
}

void UItemListWidget::OnClickedButtonHelmet()
{
	init();
	
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Equipment)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr && equipInfo->equipmentType == EEquipmentType::Helmet)
				{

					auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());

					if (button != nullptr)
					{
						button->SetItemListWidget(this);
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
	
}

void UItemListWidget::OnClickedButtonConsume()
{
	init();
	
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player == nullptr)
	{
		return;
	}
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr && itemButtonWidgetClass != nullptr)
	{
		auto inven = invenComp->GetInventory();
		for (auto iter = inven.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->GetItemInfo()->item_Type == EItemType::Consume)
			{
				auto equipInfo = iter->Value->GetEquipmentInfo();

				if (equipInfo != nullptr)
				{

					auto button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), itemButtonWidgetClass.Get());

					if (button != nullptr)
					{
						button->SetItemListWidget(this);
						button->SetInformation(iter->Value->GetItemInfo(), iter->Value->item_Count);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
	
}

void UItemListWidget::UpdateItemList(const FName& itemCode, const int32& itemCount)
{

	for (auto i = 0; i < ScrollBox_ItemList->GetChildrenCount(); i++)
	{
		auto button = Cast<UItemButtonWidget>(ScrollBox_ItemList->GetChildAt(i));
		if (button != nullptr)
		{
			if (button->GetItemCode().IsEqual(itemCode) == true)
			{
				if (itemCount == 0)
				{
					button->RemoveFromParent();
				}
				else
				{

					button->UpdateItemCount(itemCount);
				}
				break;
			}
		}
	}
}

void UItemListWidget::ShowItemMenu(const FName& item_Code)
{
		auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	
		if (player == nullptr)
		{
			return;
		}
		
		auto ivenComp = player->GetinventoryComponent();
		if (ivenComp == nullptr)
		{
			return;
		}

		if (itemMenuWidgetClass != nullptr)
	{
		if (itemMenuWidget == nullptr)
		{
			itemMenuWidget = CreateWidget<UItemMenuWidget>(GetOwningPlayer(), itemMenuWidgetClass.Get());
		}

		//생성 하는부분
		itemMenuWidget->SetItemCode(item_Code);

		auto mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer());

		itemMenuWidget->SetPositionInViewport(mousePos, false);

		if (ivenComp->GetItemInfo(item_Code)->item_Type != EItemType::Consume)
		{
			itemMenuWidget->DisableUseButton();
		}
		else
		{
			itemMenuWidget->EnableUseButton();
		}

			if (itemMenuWidget->IsInViewport() == false)
		{
			itemMenuWidget->AddToViewport();
		}
	}

}

void UItemListWidget::RemoveItemMenu()
{
	if (itemMenuWidget != nullptr)
	{
		itemMenuWidget->RemoveFromParent();
	}
}
