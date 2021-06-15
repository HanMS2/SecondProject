// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NPC/NPCSellItemWidget.h"
#include "NPCBuyItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UNPCBuyItemWidget : public UNPCSellItemWidget
{
	GENERATED_BODY()
protected:

	virtual void NativeConstruct() override;
};
