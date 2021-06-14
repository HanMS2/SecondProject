// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemTypes.h"

#include "ItemButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UItemButtonWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
		class UButton* Button_Item;
	UPROPERTY()
		class UImage* Image_ItemImage;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_Description;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemCount;

	FName item_Code;

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UToolTipWidget> toolTipWidgetClass;
	UPROPERTY()
		UToolTipWidget* MytoolTipWidget;
	UPROPERTY()
	class UItemListWidget* UMG_ItemList;

public:
	void SetInformation(const FItemInformation* info, const int32& item_Count);
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnHoveredButtonItem();
	UFUNCTION()
		void OnClickedButtonItem();
	const FName GetItemCode() { return item_Code; }

	void UpdateItemCount(const int32& item_Count);
	void SetItemListWidget(UItemListWidget* p_widget);



};
