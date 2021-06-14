// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/DragableWidget.h"

#include "Item/ItemTypes.h"
#include "DragItemButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UDragItemButtonWidget : public UDragableWidget
{
	GENERATED_BODY()
	
	UPROPERTY()
		class UImage* Image_ItemImage;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_Description;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemCount;

	FName item_Code;

public:
	void SetInformation(const FItemInformation* info, const int32& item_Count);
	
	const FName& GetItemCode() { return item_Code; }

	//UFUNCTION()
	//virtual void NativeConstruct() override;


};
