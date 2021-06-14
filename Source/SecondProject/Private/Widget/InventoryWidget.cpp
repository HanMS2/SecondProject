// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryWidget.h"

#include "Widget/ItemInformationWidget.h"
#include "Widget/PlayerInformationWidget.h"
#include "Widget/ItemListWidget.h"

#include "Character/Player/PlayerCharacter.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Widget/EquipmentWidget.h"



void UInventoryWidget::OnClickedButtonInventory()
{
	WidgetSwitcher_Switcher->SetActiveWidgetIndex(0);
}

void UInventoryWidget::OnClickedButtonEquipment()
{
	WidgetSwitcher_Switcher->SetActiveWidgetIndex(1);
	UMG_Equipment->Init();
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OnVisibilityChanged.AddUniqueDynamic(this, &UInventoryWidget::OnvisibilityChange);
	
	Button_Inventroy->OnClicked.AddUniqueDynamic(this, &UInventoryWidget::OnClickedButtonInventory);
	Button_Equipment->OnClicked.AddUniqueDynamic(this, &UInventoryWidget::OnClickedButtonEquipment);


}

void UInventoryWidget::OnvisibilityChange(ESlateVisibility InVisibility)
{
	if (InVisibility == ESlateVisibility::Visible)
	{
		auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
		if (player != nullptr)
		{
			UMG_PlayerInformation->SetPlayerInformation(player->GetStatusComponent());
			UMG_ItemList->init();
			UMG_ItemList->UpdateItemList(player->GetinventoryComponent());
			UMG_ItemInformation->init();

		}
	}
	else if(InVisibility == ESlateVisibility::Hidden)
	{
		UMG_ItemList->RemoveItemMenu();
	}

}

void UInventoryWidget::UpdateItemListButton(const FName& itemCode, const int32& itemCount)
{
	UMG_ItemList->UpdateItemList(itemCode, itemCount);

}
