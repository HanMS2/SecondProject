// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SystemMsgWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API USystemMsgWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UTextBlock* TextBlock_Msg;

public:
	void SetText(FName msg, FLinearColor textColor);
};
