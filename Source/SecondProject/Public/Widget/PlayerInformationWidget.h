// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UPlayerInformationWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
		class UTextBlock* TextBlock_HP;
	UPROPERTY()
		class UTextBlock* TextBlock_SP;

	UPROPERTY()
		class UTextBlock* TextBlock_Dam;
	UPROPERTY()
		class UTextBlock* TextBlock_Def;
	

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetPlayerInformation(class UStatusComponent* statComp);
};
