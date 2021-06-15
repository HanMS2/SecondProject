// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPC/NPCSellItemWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Character/NPC/NPCBase.h"
#include "Widget/NPC/NPCSellItemButtonWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Component/StatusComponent.h"

void UNPCSellItemWidget::OnClickedButtonClose()
{
	RemoveFromParent();
}

void UNPCSellItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Close->OnClicked.AddUniqueDynamic(this,&UNPCSellItemWidget::OnClickedButtonClose);
	ScrollBox_ItemList->ClearChildren();

	if (npcActionType == ENPCActionType::SELL)
	{
		if (ownerNPC != nullptr)
		{
			auto item = ownerNPC->GetSavedSellItemList();
			if (sellButtonWidgetClass != nullptr)
			{
				for (auto i = 0; i < item.Num(); i++)
				{

					auto button = CreateWidget<UNPCSellItemButtonWidget>(GetOwningPlayer(), sellButtonWidgetClass.Get());
					if (button != nullptr)
					{
						button->SetInformation(&item[i], ownerNPC);
						ScrollBox_ItemList->AddChild(button);
					}
				}
			}
		}
	}
	Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetStatusComponent()->
		OnChangeGold.AddUniqueDynamic(this, &UNPCSellItemWidget::SetGoldText);


	TextBlock_Gold->SetText(FText::AsNumber(Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetStatusComponent()->GetGold()));
}

void UNPCSellItemWidget::SetGoldText(const int32& gold)
{
	TextBlock_Gold->SetText(FText::AsNumber(gold));
}
