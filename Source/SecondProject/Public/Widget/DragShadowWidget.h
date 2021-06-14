// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragShadowWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UDragShadowWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class USizeBox* SizeBox_Override;

public:

	UPROPERTY()
		class UUserWidget* WidgetReference;
	UPROPERTY()
		FVector2D dragOffset;

	virtual void NativeConstruct()override;
};
