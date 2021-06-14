// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UBossWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UTextBlock* TextBlock_MonsterName;
	UPROPERTY()
		class UProgressBar* ProgressBar_HP;
	UPROPERTY()
		class AMonster* monster;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:

	void SetMonster(class AMonster* m);
};
