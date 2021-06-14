// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Controller/CustomController.h"
#include "Blueprint/UserWidget.h"//<<요 안에 위젯 생성 함수 있음.
#include "Widget/InventoryWidget.h"
#include "Character/Monster/Monster.h"
#include "Widget/BossWidget.h"
#include "Character/NPC/NPCBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget/NPC/NPCDialogWidget.h"

void ACustomController::BeginPlay()
{
	Super::BeginPlay();

	if (mainWidgetClass != nullptr) {
		mainWidget = CreateWidget<UUserWidget>(this, mainWidgetClass.Get());
		if (mainWidget != nullptr) {
			mainWidget->AddToViewport();
		}
	}

	if (lockOnWidgetClass!=nullptr) {
		lockOnWidget = CreateWidget<UUserWidget>(this, lockOnWidgetClass.Get());
		if (lockOnWidget != nullptr) {
			lockOnWidget->AddToViewport();
			lockOnWidget->SetDesiredSizeInViewport(FVector2D(50, 50));
			lockOnWidget->SetVisibility(ESlateVisibility::Hidden);

		}
	}
}

void ACustomController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interaction", IE_Pressed, this, &ACustomController::ClickMouseLeftButton);

	//마우스 커서보기.
	InputComponent->BindAction("ShowMouseCursor", IE_Pressed, this, &ACustomController::ShowMouseCursor);
}

void ACustomController::ClickMouseLeftButton()
{
	UE_LOG(LogTemp,Log,TEXT("Click"));

	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel6));

	FHitResult Hit;

	if (GetHitResultUnderCursorForObjects(ObjectTypes, false, Hit))
	{
		if (Hit.GetActor()->IsA<ANPCBase>())
		{
			bShowMouseCursor = true;
			Cast<ANPCBase>(Hit.GetActor())->Interaction(this);
			//	UWidgetBlueprintLibrary::SetInputMode_UIOnly(this,DialogWidget);
		}		
	}
}

void ACustomController::AddBossWidget(AMonster* monster)
{
	if (monster != nullptr)
	{
		if (bossWidgetClass != nullptr)
		{
			if (bossWidget != nullptr && bossWidget->IsInViewport() == false)
			{
				bossWidget->AddToViewport();
			}
			if (bossWidget == nullptr)
			{
				bossWidget = CreateWidget<UBossWidget>(this, bossWidgetClass.Get());
				bossWidget->SetMonster(monster);
				bossWidget->AddToViewport();
			}
		}
	}
}

void ACustomController::RemoveBossWidget()
{
	if (bossWidget != nullptr)
	{
		bossWidget->RemoveFromParent();
	}
}


void ACustomController::ShowMouseCursor()
{
	bShowMouseCursor = !bShowMouseCursor;
}


void ACustomController::SetLockOnWidgetPos(AActor* target)
{
	if (lockOnWidget != nullptr && target != nullptr) {
		FVector2D screenPos;
		if (ProjectWorldLocationToScreen(target->GetActorLocation(), screenPos)) {
			screenPos.X -= 25;
			screenPos.Y -= 25;
			lockOnWidget->SetPositionInViewport(screenPos);
		}
	}
}

void ACustomController::SetVisibilityLockOnWidget(ESlateVisibility newVisible)
{
	if (lockOnWidget != nullptr) {
		lockOnWidget->SetVisibility(newVisible);
	}
}

void ACustomController::ShowInventory()
{
	if (inventoryWidget == nullptr) {
		if (inventoryWidgetClass != nullptr) {
			inventoryWidget = CreateWidget<UInventoryWidget>(this, inventoryWidgetClass.Get());
			inventoryWidget->AddToViewport();
			inventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}


	if (inventoryWidget->GetVisibility() == ESlateVisibility::Hidden) {
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
		inventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		SetInputMode(FInputModeGameOnly());
	
		inventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

UItemInformationWidget* ACustomController::GetItemInformationWidget()
{
	if (inventoryWidget != nullptr)
	{
		return inventoryWidget->GetUMG_ItemInformation();
	}
	return nullptr;
}
