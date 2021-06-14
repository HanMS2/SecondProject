// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UEquipmentItemListWidget* UMG_EquipmentItemList;
			
		UPROPERTY()
			class UEquipmentButtonWidget* UMG_EquipmentButton_Helmet;
		UPROPERTY()
			class UEquipmentButtonWidget* UMG_EquipmentButton_Weapon;
		UPROPERTY()
			class UEquipmentButtonWidget* UMG_EquipmentButton_Chest;
		UPROPERTY()
			class UEquipmentButtonWidget* UMG_EquipmentButton_Shield;
		UPROPERTY()
			class UEquipmentButtonWidget* UMG_EquipmentButton_Glove;
		UPROPERTY()
			class UEquipmentButtonWidget* UMG_EquipmentButton_Leg;
		UPROPERTY()
			class UEquipmentButtonWidget* UMG_EquipmentButton_Boots;

		UPROPERTY()
			class UTextBlock* TextBlock_Damage;
		UPROPERTY()
			class UTextBlock* TextBlock_Defence;

		UPROPERTY()
			class UHorizontalBox* HorizontalBox_Quick;
		
		UPROPERTY()
			TArray<class UEquipmentButtonWidget*> QuickButtons;


public:
	void Init();
	UFUNCTION()
		virtual void NativeConstruct() override;

	UFUNCTION()
		void SetPlayerInformation(class UStatusComponent* statComp);

};
