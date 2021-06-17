// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SystemMsgWidget.h"
#include "Components/TextBlock.h"


void USystemMsgWidget::SetText(FName msg, FLinearColor textColor)
{
	UE_LOG(LogTemp, Log, TEXT("%s"),*msg.ToString());
	TextBlock_Msg->SetText(FText::FromName(msg));
	TextBlock_Msg->ColorAndOpacity = FSlateColor(textColor);	
}
