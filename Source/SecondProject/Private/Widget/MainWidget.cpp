// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Component/StatusComponent.h"

#include "Components/ProgressBar.h"
#include "Components/ScrollBox.h"
#include "Widget/SystemMsgWidget.h"
#include "Character/Player/Controller/CustomController.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (player != nullptr) {
		auto statusComp = player->GetStatusComponent();
		if (statusComp) {
			ProgressBar_HP->SetPercent(statusComp->GetHPPercent());
			ProgressBar_SP->SetPercent(statusComp->GetSPPercent());
		}
	}

	Cast<ACustomController>(GetOwningPlayer())->OnSystemMsg.AddUniqueDynamic(this, &UMainWidget::AddSystemMsg);
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {

	Super::NativeTick(MyGeometry, InDeltaTime);
	if (player != nullptr) {
		auto statusComp = player->GetStatusComponent();
		if (statusComp) {
			ProgressBar_HP->SetPercent(FMath::FInterpTo(ProgressBar_HP->Percent, statusComp->GetHPPercent(), InDeltaTime, 5.f));
			ProgressBar_SP->SetPercent(FMath::FInterpTo(ProgressBar_SP->Percent, statusComp->GetSPPercent(), InDeltaTime, 5.f));
		}
	}
}

void UMainWidget::AddSystemMsg(FName msg, enum ESystemMsgType type)
{
	if (SystemMsgWidgetClass != nullptr)
	{
		auto msgWidget = CreateWidget<USystemMsgWidget>(GetOwningPlayer(), SystemMsgWidgetClass.Get());

		if (msgWidget != nullptr)
		{
			switch (type)
			{
			case ESystemMsgType::NORMAL:
				msgWidget->SetText(msg, FLinearColor::Gray);
				break;
			case ESystemMsgType::LEVELUP:
				msgWidget->SetText(msg, FLinearColor::Yellow);
				break;
			case ESystemMsgType::GETITEM:
				msgWidget->SetText(msg, FLinearColor::Green);
				break;
			default:
				break;
			}
		}

	}
}
