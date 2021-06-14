// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ToolTipWidget.h"
#include "Components/TextBlock.h"

void UToolTipWidget::SetText(FName Description)
{
	TextBlock_ToolTip2->SetText(FText::FromName(Description));
}
