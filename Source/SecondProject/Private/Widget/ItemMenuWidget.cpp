// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemMenuWidget.h"
#include "Components/Button.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/Component/InventoryComponent.h"

void UItemMenuWidget::OnClickedButtonUse()
{
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());

	if (player != nullptr)
	{
		player->GetinventoryComponent()->UseItem(itemCode, player);
	}

	RemoveFromParent();
}

void UItemMenuWidget::OnClickedButtonDrop()
{
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());

	if (player != nullptr)
	{
		player->GetinventoryComponent()->DropItem(itemCode);
	}
}

void UItemMenuWidget::OnClickedButtonRemove()
{
	auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());

	if (player != nullptr)
	{
		player->GetinventoryComponent()->RemoveItem(itemCode);
	}
	RemoveFromParent();
}

void UItemMenuWidget::OnClickedButtonCancle()
{
	RemoveFromParent();
}

void UItemMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Use->OnClicked.AddUniqueDynamic(this, &UItemMenuWidget::OnClickedButtonUse);
	Button_Remve->OnClicked.AddUniqueDynamic(this, &UItemMenuWidget::OnClickedButtonRemove);
	Button_Drop->OnClicked.AddUniqueDynamic(this, &UItemMenuWidget::OnClickedButtonDrop);
	Button_Cancle->OnClicked.AddUniqueDynamic(this, &UItemMenuWidget::OnClickedButtonCancle);

}

void UItemMenuWidget::DisableUseButton()
{
	//Button_Use->SetIsEnabled(false);
}

void UItemMenuWidget::EnableUseButton()
{
	Button_Use->SetIsEnabled(true);
}
