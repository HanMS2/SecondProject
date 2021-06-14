// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemListWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UItemListWidget : public UUserWidget
{
	GENERATED_BODY()


	UPROPERTY()
		class UButton* Button_All;
	UPROPERTY()
		class UButton* Button_Weapon;
	UPROPERTY()
		class UButton* Button_Shield;
	UPROPERTY()
		class UButton* Button_Chest;
	UPROPERTY()
		class UButton* Button_Glove;
	UPROPERTY()
		class UButton* Button_Boots;
	UPROPERTY()
		class UButton* Button_Leg;
	UPROPERTY()
		class UButton* Button_Helmet;
	UPROPERTY()
		class UButton* Button_Consume;

protected:

	UPROPERTY()
		class UScrollBox* ScrollBox_ItemList;

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItemButtonWidget> itemButtonWidgetClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItemMenuWidget> itemMenuWidgetClass;
	UPROPERTY()
		UItemMenuWidget* itemMenuWidget;

public:
	void init();

	void NativeConstruct();
	virtual void UpdateItemList(class UInventoryComponent* invenComp);

	UFUNCTION()
		virtual void OnClickedButtonItem();
	UFUNCTION()
		virtual void OnClickedButtonAll();
	UFUNCTION()
		virtual void OnClickedButtonWeapon();
	UFUNCTION()
		virtual void OnClickedButtonSheild();
	UFUNCTION()
		virtual void OnClickedButtonChest();
	UFUNCTION()
		virtual void OnClickedButtonGlove();
	UFUNCTION()
		virtual void OnClickedButtonLeg();
	UFUNCTION()
		virtual void OnClickedButtonBoots();
	UFUNCTION()
		virtual void OnClickedButtonHelmet();
	UFUNCTION()
		virtual void OnClickedButtonConsume();

public:

	void UpdateItemList(const FName& itemCode, const int32& itemCount);

	void ShowItemMenu(const FName& item_Code);

	void RemoveItemMenu();



};
