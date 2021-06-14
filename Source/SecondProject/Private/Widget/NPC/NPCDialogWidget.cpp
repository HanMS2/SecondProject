﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPC/NPCDialogWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Character/NPC/NPCBase.h"



void UNPCDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Sell->OnClicked.AddUniqueDynamic(this, &UNPCDialogWidget::OnClickedButtonSell);
	Button_Buy->OnClicked.AddUniqueDynamic(this, &UNPCDialogWidget::OnClickedButtonBuy);
	Button_Chat->OnClicked.AddUniqueDynamic(this, &UNPCDialogWidget::OnClickedButtonChat);
	Button_Close->OnClicked.AddUniqueDynamic(this, &UNPCDialogWidget::OnClickedButtonClose);


}

void UNPCDialogWidget::OnClickedButtonChat()
{
	
	if (ownerNPC != nullptr)
	{
		auto chat = ownerNPC->GetChat();
		if (chat.Num() > 0)
		{
			auto randNum = FMath::RandRange(0, chat.Num() - 1);
			TextBlock_Dialog->SetText(FText::FromName(chat[randNum]));

		}
		else
		{
			TextBlock_Dialog->SetText(FText::FromString("잡담이 비었습니다!"));
		}
	}
}

void UNPCDialogWidget::OnClickedButtonBuy()
{


}

void UNPCDialogWidget::OnClickedButtonSell()
{

}

void UNPCDialogWidget::OnClickedButtonClose()
{
	RemoveFromParent();
	
	GetOwningPlayer()->bShowMouseCursor = false;
}

void UNPCDialogWidget::Init(ANPCBase* npc)
{
	ownerNPC = npc;

	TextBlock_NPCName->SetText(FText::FromName(npc->GetNPCName()));
	auto chat = npc->GetChat();
	if (chat.Num() > 0)
	{
		auto randNum = FMath::RandRange(0, chat.Num() - 1);
		TextBlock_Dialog->SetText(FText::FromName(chat[randNum]));

	}
	else
	{
		TextBlock_Dialog->SetText(FText::FromString("잡담이 비었습니다!"));
	}
	


}
