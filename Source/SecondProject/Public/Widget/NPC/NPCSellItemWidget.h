// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCSellItemWidget.generated.h"



UENUM(BlueprintType)
enum class ENPCActionType : uint8
{
	SELL,
	BUY,
};


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

	UPROPERTY()
		class UTextBlock* TextBlock_Gold;

	UPROPERTY(EditAnywhere)
		ENPCActionType npcActionType;
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

	UFUNCTION()
		void SetGoldText(const int32& gold);
};
