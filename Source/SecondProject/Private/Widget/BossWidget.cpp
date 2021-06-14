// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BossWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Character/Monster/Monster.h"
#include "Character/Component/StatusComponent.h"

void UBossWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (monster != nullptr)
	{
		auto statusComp = monster->GetStatusComponent();
		if (statusComp)
		{
			ProgressBar_HP->SetPercent(FMath::FInterpTo(ProgressBar_HP->Percent, statusComp->GetHPPercent(), InDeltaTime, 5.f));
		}
	}
}

void UBossWidget::SetMonster(AMonster* m)
{
	monster = m;
	TextBlock_MonsterName->SetText(FText::FromName(monster->monster_Name));
}
