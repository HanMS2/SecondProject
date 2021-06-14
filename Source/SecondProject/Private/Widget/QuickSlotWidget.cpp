// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuickSlotWidget.h"

#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/Component/InventoryComponent.h"
#include "Engine/Texture2D.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	
	if (player != nullptr)
	{
		// 딜리게이트 바인딩 기억하자!!!!
		player->GetinventoryComponent()->AddQuickEvent.AddUniqueDynamic(this, &UQuickSlotWidget::ChangeQuickSlotEvent);

		player->GetinventoryComponent()->UseQuickEvent.AddUniqueDynamic(this, &UQuickSlotWidget::UseQuickSlotEvent);
	
	}

}

void UQuickSlotWidget::ChangeQuickSlotEvent(UTexture2D* texture, const int32& count)
{
	Image_Item->SetBrushFromTexture(texture);
	
	TextBlock_Count->SetText(FText::AsNumber(count));
}

void UQuickSlotWidget::UseQuickSlotEvent(const int32& count)
{
	TextBlock_Count->SetText(FText::AsNumber(count));
}
