// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCSellItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UNPCSellItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UScrollBox* ScrollBox_ItemList;

	UPROPERTY()
		class UButton* Button_Close;
public:
	UFUNCTION()
		void OnClickedButtonClose();

	virtual void NativeConstruct() override;
	
	UPROPERTY()
		class ANPCBase* ownerNPC;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UNPCSellItemButtonWidget> sellButtonWidgetClass;
public:
	void SetNPC(ANPCBase* npc) { ownerNPC = npc; }

};
