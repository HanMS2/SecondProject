// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DragShadowWidget.h"
#include "Components/SizeBox.h"

void UDragShadowWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (WidgetReference != nullptr)
	{
		auto size = WidgetReference->GetDesiredSize();
		SizeBox_Override->SetHeightOverride(size.Y);
		SizeBox_Override->SetWidthOverride(size.X);
	}
}
