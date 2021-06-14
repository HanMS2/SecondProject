// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EquipmentWidget.h"

#include "..\..\Public\Widget\EquipmentWidget.h"
#include "Widget/EquipmentItemListWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Widget/EquipmentButtonWidget.h"
#include "Character/Player/Component/InventoryComponent.h"


void UEquipmentWidget::Init()
{

	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player != nullptr)
	{
		UMG_EquipmentItemList->UpdateItemList(player->GetinventoryComponent());
	}
}

void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player != nullptr)
	{
		player->GetinventoryComponent()->EquipEvent.AddUniqueDynamic(this, &UEquipmentWidget::SetPlayerInformation);
		player->GetinventoryComponent()->UnEquipEvent.AddUniqueDynamic(this, &UEquipmentWidget::SetPlayerInformation);
	}

	for (auto i = 0; i < HorizontalBox_Quick->GetChildrenCount(); i++)
	{
		auto button = Cast<UEquipmentButtonWidget>(HorizontalBox_Quick->GetChildAt(i));
		
		if (button != nullptr)
		{
			button->SetEquipmentButtonType(EEquipmentButtonType::Consume);
			button->SetIndex(i);
			button->SetHorizontalBox_Quick(HorizontalBox_Quick);
			QuickButtons.Emplace(button);

		}
	
	}


}

void UEquipmentWidget::SetPlayerInformation(UStatusComponent* statComp)
{
	if (statComp != nullptr)
	{	
		TextBlock_Damage->SetText(FText::AsNumber(statComp->GetDam()));
		TextBlock_Defence->SetText(FText::AsNumber(statComp->GetDef()));
	}
}
