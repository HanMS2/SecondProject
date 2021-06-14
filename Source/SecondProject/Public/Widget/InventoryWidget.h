// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
		class UButton* Button_Inventroy;
	UPROPERTY()
		class UButton* Button_Equipment;
	UPROPERTY()
		class UWidgetSwitcher* WidgetSwitcher_Switcher;

	UPROPERTY()
		class UItemListWidget* UMG_ItemList;
	UPROPERTY()
		class UItemInformationWidget* UMG_ItemInformation;
	UPROPERTY()
		class UPlayerInformationWidget* UMG_PlayerInformation;
	
	UPROPERTY()
		class UEquipmentWidget* UMG_Equipment;
protected:
	UFUNCTION()
		void OnClickedButtonInventory();
	UFUNCTION()
		void OnClickedButtonEquipment();


public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnvisibilityChange(ESlateVisibility InVisibility);

	class UItemInformationWidget* GetUMG_ItemInformation() { return UMG_ItemInformation; }

	void UpdateItemListButton(const FName& itemCode, const int32& itemCount);
};
