// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPC/NPCSellItemWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Character/NPC/NPCBase.h"
#include "Widget/NPC/NPCSellItemButtonWidget.h"

void UNPCSellItemWidget::OnClickedButtonClose()
{
	RemoveFromParent();
}

void UNPCSellItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddUniqueDynamic(this,&UNPCSellItemWidget::OnClickedButtonClose);
	ScrollBox_ItemList->ClearChildren();

	if (ownerNPC != nullptr)
	{
		auto item = ownerNPC->GetSellItemList();
		if (sellButtonWidgetClass != nullptr)
		{
			for (auto i = 0; i < item.Num(); i++)
			{


				auto button = CreateWidget<UNPCSellItemButtonWidget>(GetOwningPlayer(), sellButtonWidgetClass.Get());
				if (button != nullptr)
				{
					button->SetInformation(item[i]);
					ScrollBox_ItemList->AddChild(button);
				}
			}
		}
	
	}
}
