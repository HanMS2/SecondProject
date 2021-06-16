// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPC/NPCBuyItemWidget.h"

#include "Character/Player/Component/InventoryComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Widget/NPC/NPCBuyItemButtonWidget.h"
#include "Components/ScrollBox.h"

void UNPCBuyItemWidget::NativeConstruct()
{
	npcActionType = ENPCActionType::BUY;
	Super::NativeConstruct();
	
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	auto invenComp = player->GetinventoryComponent();
	
	for (auto item : invenComp->GetInventory())
	{
		//item.Value->GetItemInfo();

		auto button = CreateWidget<UNPCBuyItemButtonWidget>(GetOwningPlayer(), sellButtonWidgetClass.Get());
		if (button != nullptr)
		{
			button->SetInformation(item.Value->GetItemInfo(), item.Value->item_Count, ownerNPC);
			ScrollBox_ItemList->AddChild(button);
		}
	}

}