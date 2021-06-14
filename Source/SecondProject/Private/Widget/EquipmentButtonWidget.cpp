// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EquipmentButtonWidget.h"
#include "..\..\Public\Widget\EquipmentButtonWidget.h"

#include "Widget/WidgetDragDropOper.h"
#include "Widget/DragItemButtonWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/Component/InventoryComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

void UEquipmentButtonWidget::Init()
{
    //퀵슬롯 배열에 코드 삭제 필요.
    auto invenComp = Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetinventoryComponent();

    if (invenComp != nullptr)
    {
        invenComp->Removequick(item_Code);
    }
    item_Code = NAME_None;
    TextBlock_ItemCount->SetText(FText::GetEmpty());
    if (emptyTexture != nullptr)
    {
        Image_Item->SetBrushFromTexture(emptyTexture);
    }
}

void UEquipmentButtonWidget::SetItemInformation(const FItemInformation* info, const int32& itemCount)
{
    
    if (buttonType == EEquipmentButtonType::Consume)
    {
        for (auto i = 0; i < quickListBox->GetChildrenCount(); i++)
        {
            auto button = Cast<UEquipmentButtonWidget>(quickListBox->GetChildAt(i));

            if (button != nullptr)
            {
                if (button != this)
                {
                    if (button->item_Code.IsEqual(item_Code))
                    {
                        button->Init();
                        break;
                    }                                    
                }
            }
        }
        Image_Item->SetBrushFromTexture(info->item_Image);
        TextBlock_ItemCount->SetText(FText::AsNumber(itemCount));
    }
  


}

void UEquipmentButtonWidget::SetItemInformation(const FEquipmentInformation* info)
{
    if (buttonType != EEquipmentButtonType::Consume)
    {
        auto equipType = info->equipmentType;
        switch (buttonType)
        {
        case EEquipmentButtonType::Weapon:
            if (equipType == EEquipmentType::Weapon)
            {
                Image_Item->SetBrushFromTexture(info->item_Image);
                auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
                player->GetinventoryComponent()->UseItem(item_Code, player);
            }
            break;
        case EEquipmentButtonType::Shield:
            if (equipType == EEquipmentType::Shield)
            {
                Image_Item->SetBrushFromTexture(info->item_Image);
                auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
                player->GetinventoryComponent()->UseItem(item_Code, player);
            }
            break;
        case EEquipmentButtonType::Helmet:
            if (equipType == EEquipmentType::Helmet)
            {
                Image_Item->SetBrushFromTexture(info->item_Image);
                auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
                player->GetinventoryComponent()->UseItem(item_Code, player);
            }
            break;
        case EEquipmentButtonType::Boots:
            if (equipType == EEquipmentType::Boots)
            {
                Image_Item->SetBrushFromTexture(info->item_Image);
                auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
                player->GetinventoryComponent()->UseItem(item_Code, player);
            }
            break;
        case EEquipmentButtonType::Chest:
            if (equipType == EEquipmentType::Chest)
            {
                Image_Item->SetBrushFromTexture(info->item_Image);
                auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
                player->GetinventoryComponent()->UseItem(item_Code, player);
            }
            break;
        case EEquipmentButtonType::Legs:
            if (equipType == EEquipmentType::Legs)
            {
                Image_Item->SetBrushFromTexture(info->item_Image);
                auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
                player->GetinventoryComponent()->UseItem(item_Code, player);
            }
            break;

        case EEquipmentButtonType::Gloves:
            if (equipType == EEquipmentType::Gloves)
            {
                Image_Item->SetBrushFromTexture(info->item_Image);
                auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
                player->GetinventoryComponent()->UseItem(item_Code, player);
            }
            break;
        default:
            break;
        }
                TextBlock_ItemCount->SetText(FText::GetEmpty());
              
                
    }

}

bool UEquipmentButtonWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    if (InOperation != nullptr)
    {
       auto oper = Cast<UWidgetDragDropOper>(InOperation);
       if (oper != nullptr)
       {
        auto button = Cast<UDragItemButtonWidget>(oper->widgetReference);
        if (button != nullptr && button->GetItemCode().IsEqual(NAME_None) == false)
        {
            item_Code = button->GetItemCode();
            auto invenComp = Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetinventoryComponent();
          auto info = invenComp->GetItemInfo(item_Code) ;
          auto item = *invenComp->GetItem(item_Code);
        
          if (item.GetEquipmentType() == EEquipmentType::None)
          {
              SetItemInformation(item.GetItemInfo(), item.item_Count);
              invenComp->AddQuick(item_Code, index);
          }
          else
          {

              SetItemInformation(item.GetEquipmentInfo());
          }
          return true;

          /*
          if (item != nullptr)
          {
              
              if (invenComp->GetEquipmentType(item_Code) == EEquipmentType::None)
              {
              
                  SetItemInformation(info, item->item_Count);
              }
              else
              {

                  SetItemInformation(invenComp->GetEquipmentInformation(item_Code));
              }

              
              return true;
          }
          */
        }

        auto quickButton = Cast<UEquipmentButtonWidget>(oper->widgetReference);
        if (quickButton != nullptr && quickButton->item_Code.IsEqual(NAME_None)==false)
        {

            item_Code = quickButton->item_Code;
            
            auto invenComp = Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetinventoryComponent();
            auto info = invenComp->GetItem(item_Code);
            if (info != nullptr)
            {
                auto item = *invenComp->GetItem(item_Code);
                SetItemInformation(item.GetItemInfo(), item.item_Count);
                invenComp->AddQuick(item_Code, index);

            }
            return true;
        }
       }
    }
    return false;
}

FReply UEquipmentButtonWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);


    if (InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")) == true)
    {
        //UE_LOG(LogTemp, Log, TEXT("mouse Right Button"));
        if (item_Code.IsEqual(NAME_None) == false)
        {
            auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
            player->GetinventoryComponent()->UseItem(item_Code, player);

            Init();
        }


//        return FReply::Handled();
    }
    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
  //  return FReply::Unhandled();
}
