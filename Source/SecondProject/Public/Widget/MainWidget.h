// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (OverrideNativeName = "ProgressBar_HP"))
		class UProgressBar* ProgressBar_HP;
	UPROPERTY()
		class UProgressBar* ProgressBar_SP;
	UPROPERTY()
		class APlayerCharacter* player;
	UPROPERTY()
		class UQuickSlotWidget* UMG_QuickSlot;

	UPROPERTY()
		class UScrollBox* ScrollBox_SystemMessage;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USystemMsgWidget> SystemMsgWidgetClass;

public:

	UFUNCTION()
		void AddSystemMsg(FName msg,enum ESystemMsgType type);

};
