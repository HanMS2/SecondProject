// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ItemListWidget.h"
#include "EquipmentItemListWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UEquipmentItemListWidget : public UItemListWidget
{
	GENERATED_BODY()

protected:

		UPROPERTY(EditAnywhere)
		TSubclassOf<class UDragItemButtonWidget> dragItemButtonWidgetclass;

		virtual void OnClickedButtonItem();

		virtual void OnClickedButtonAll();

		virtual void OnClickedButtonWeapon();

		virtual void OnClickedButtonSheild();
		virtual void OnClickedButtonChest();
		virtual void OnClickedButtonGlove();
		virtual void OnClickedButtonLeg();
		virtual void OnClickedButtonBoots();
		virtual void OnClickedButtonHelmet();
		virtual void OnClickedButtonConsume();

public:

		virtual void UpdateItemList(class UInventoryComponent* invenComp);
};
