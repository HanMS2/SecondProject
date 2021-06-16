// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomController.generated.h"


UENUM(BlueprintType)
enum class ESystemMsgType : uint8
{
	NORMAL,
	LEVELUP,
	GETITEM
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSystemMsg, FName, msg, ESystemMsgType, type);

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API ACustomController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> mainWidgetClass;
	UPROPERTY()
		UUserWidget* mainWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> lockOnWidgetClass;
	UPROPERTY()
		UUserWidget* lockOnWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UInventoryWidget> inventoryWidgetClass;
	UPROPERTY()
		UInventoryWidget* inventoryWidget;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent()override;

	UFUNCTION()
		void ClickMouseLeftButton();

	void ShowMouseCursor();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UBossWidget> bossWidgetClass;
	UPROPERTY()
		UBossWidget* bossWidget;

	UPROPERTY()
		class UNPCDialogWidget* DialogWidget;


public:
	void AddBossWidget(class AMonster* monster);
	void RemoveBossWidget();
	void SetLockOnWidgetPos(AActor* target);
	void SetVisibilityLockOnWidget(ESlateVisibility newVisible);

	void ShowInventory();

	class UItemInformationWidget* GetItemInformationWidget();

	UInventoryWidget* GetinventoryWidget() {return inventoryWidget;	}

	void SetDialogWidget(class UNPCDialogWidget* dialog) { DialogWidget = dialog; }
	class UNPCDialogWidget* GetDialogWidget() { return DialogWidget; }

	FSystemMsg OnSystemMsg;

};
