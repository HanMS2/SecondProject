// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/DragableWidget.h"


#include "Item/ItemTypes.h"
#include "EquipmentButtonWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEquipmentButtonType : uint8
{
	Weapon,
	Shield,
	Helmet,
	Gloves,
	Chest,
	Legs,
	Boots,
	Consume,

};



UCLASS()
class SECONDPROJECT_API UEquipmentButtonWidget : public UDragableWidget
{
	GENERATED_BODY()

protected:

		UPROPERTY()
		class UImage* Image_Item;
		UPROPERTY()
		class UTextBlock* TextBlock_ItemCount;

		UPROPERTY(EditAnywhere)
			EEquipmentButtonType buttonType;


		UPROPERTY(EditAnywhere)
			class UTexture2D* emptyTexture;

		FName item_Code = NAME_None;

		class UHorizontalBox* quickListBox;

		int32 index = -1;
public:

	void Init();
	void SetItemInformation(const FItemInformation* info, const int32& itemCount);
	void SetItemInformation(const FEquipmentInformation* info);
	void SetEquipmentButtonType(EEquipmentButtonType type) { buttonType = type; }
	void SetHorizontalBox_Quick(class UHorizontalBox* box) { quickListBox = box; }
	void SetIndex(const int32& value) { index = value; }
	const FName& GetItemCode() { return item_Code; }
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


};
