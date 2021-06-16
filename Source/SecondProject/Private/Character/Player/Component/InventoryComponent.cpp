// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/InventoryComponent.h"

#include "Character/Player/PlayerCharacter.h"
#include "Item/ItemActor.h"
#include "Character/Player/Controller/CustomController.h"
#include "Widget/InventoryWidget.h"
#include "..\..\..\..\Public\Character\Player\Component\InventoryComponent.h"



// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	quickSlot.Init(NAME_None, 7);
	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

bool UInventoryComponent::existQuickItem()
{
	for (auto i = 0; i < quickSlot.Num(); i++)
	{
		if (quickSlot[i].IsEqual(NAME_None) == false)
		{
			return true;
		}
	}
	return false;
}

void UInventoryComponent::Removequick(const FName& itemCode)
{
	if (quickSlot.Contains(itemCode))
	{
		quickSlot.Remove(itemCode);
	}
}

void UInventoryComponent::AddQuick(const FName& itemCode, const int32& index)
{

	if (inventory.Contains(itemCode))
	{
			auto item = inventory[itemCode];
		if (index == quickIndex)
		{

			AddQuickEvent.Broadcast(item->GetItemInfo()->item_Image, item->item_Count);
		}
		else
		{
			if (quickSlot.IsValidIndex(quickIndex))
			{
				if (quickSlot[quickIndex].IsEqual(NAME_None) == true)
				{
					quickIndex = index;
					AddQuickEvent.Broadcast(item->GetItemInfo()->item_Image, item->item_Count);
				}
			}
		}

		if (quickSlot.IsValidIndex(index))
		{
			quickSlot[index] = itemCode;

		}
	}
}

void UInventoryComponent::AddItem(AItemActor* item)
{
	if (item != nullptr)
	{
		auto info = item->GetItemInformation<FItemInformation>();
		if (info != nullptr)
		{
			inventory.Add(info->item_Code, new FStoredItem(info, item->GetItemCount()));

			//컨트롤러를 들고와서 OnSystemMsg.Broadcast("~아이템을 획득했다.",ESystemMsgType::GetItem);
		}
	}
}

void UInventoryComponent::UseItem(const FName itemCode, AActor* target)
{
	if (inventory.Contains(itemCode))
	{
		auto itemClass = inventory[itemCode]->GetItemInfo()->itemClass;

		if (itemClass != nullptr)
		{
			if (inventory[itemCode]->GetItemInfo()->item_Type == EItemType::Consume)
			{
				inventory[itemCode]->item_Count--;
				//버튼의 카운트를 감소시킴

				auto controller = Cast<ACustomController>(Cast<ACharacter>(GetOwner())->GetController());

				if (controller != nullptr)
				{
					controller->GetinventoryWidget()->UpdateItemListButton(itemCode, inventory[itemCode]->item_Count);
				}
			

				if (inventory[itemCode]->item_Count < 1)
				{
					inventory.Remove(itemCode);
				}
			}
				auto item = GetWorld()->SpawnActor<AItemActor>(itemClass.Get());
				item->SetActorHiddenInGame(true);
				item->SetItemCode(itemCode);
				item->UseItem(target);
				item->Destroy();

		}
	}
}

void UInventoryComponent::DropItem(const FName itemCode)
{
	if (inventory.Contains(itemCode))
	{
		auto itemClass = inventory[itemCode]->GetItemInfo()->itemClass;

		if (itemClass != nullptr)
		{
			auto item = GetWorld()->SpawnActor<AItemActor>(itemClass.Get()
				, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
			if (item != nullptr)
			{
				item->SetItemCode(itemCode);
				item->SetItemCount(inventory[itemCode]->item_Count);
			}
		}
		auto controller = Cast<ACustomController>(Cast<ACharacter>(GetOwner())->GetController());

		if (controller != nullptr)
		{
			controller->GetinventoryWidget()->UpdateItemListButton(itemCode, 0);
		}

		inventory.Remove(itemCode);
	}
}

void UInventoryComponent::RemoveItem(const FName itemCode)
{
	if (inventory.Contains(itemCode))
	{
		inventory.Remove(itemCode);

		auto controller = Cast<ACustomController>(Cast<ACharacter>(GetOwner())->GetController());

		if (controller != nullptr && controller->GetinventoryWidget() != nullptr)
		{
			controller->GetinventoryWidget()->UpdateItemListButton(itemCode, 0);
		}
	}
}
bool UInventoryComponent::DecreaseItemCount(const FName itemCode)
{
	if (inventory.Contains(itemCode))
	{
		if (inventory[itemCode]->item_Count - 1 <= 0)
		{
			//해당 아이템을 지우면 됨.
			RemoveItem(itemCode);
			
		}
		else
		{
			inventory[itemCode]->item_Count--;
		}
			return true;
	}

	return false;

}


const FStoredItem* UInventoryComponent::GetItem(const FName& itemCode)
{
	if (inventory.Contains(itemCode))
	{
		return inventory[itemCode];
	}
	return nullptr;
}


const FItemInformation* UInventoryComponent::GetItemInfo(const FName& itemCode)
{
	if (inventory.Contains(itemCode))
	{
		return inventory[itemCode]->GetItemInfo();
	}
	return nullptr;
}
void UInventoryComponent::QuickUp()
{
	if (existQuickItem())
	{

		quickIndex++;
		if (quickSlot.IsValidIndex(quickIndex ) == true)
		{
			if (quickSlot[quickIndex].IsEqual(NAME_None) == true)
			{
				QuickUp();
			}
			else
			{
				if (inventory.Contains(quickSlot[quickIndex]))
				{					
					auto item = inventory[quickSlot[quickIndex]];
					if (item != nullptr)
					{
						AddQuickEvent.Broadcast(item->GetItemInfo()->item_Image, item->item_Count);
					}
				}				
			}
		}
		else
		{
			quickIndex = -1;
			QuickUp();
		}
	}
}
void UInventoryComponent::QuickDown()
{
	if (existQuickItem())
	{
		quickIndex--;
		if (quickSlot.IsValidIndex(quickIndex) == true)
		{
			if (quickSlot[quickIndex].IsEqual(NAME_None) == true)
			{
				QuickDown();
			}
			else
			{
				if (inventory.Contains(quickSlot[quickIndex]))
				{
					auto item = inventory[quickSlot[quickIndex]];
					if (item != nullptr)
					{
						AddQuickEvent.Broadcast(item->GetItemInfo()->item_Image, item->item_Count);
					}
				}
			}
		}
		else
		{
			quickIndex = quickSlot.Num();
			QuickDown();
		}
	}
}
void UInventoryComponent::UseQuick()
{
	if (quickSlot.IsValidIndex(quickIndex))
	{
		auto code = quickSlot[quickIndex];
		UseItem(quickSlot[quickIndex], GetOwner());
		//여기에 갯수 업데이트
		
		

		if (inventory.Contains(code))
		{
			UseQuickEvent.Broadcast(inventory[code]->item_Count);

		}
		else
		{
			UseQuickEvent.Broadcast(0);
		}

	}
}

//
//const EEquipmentType UInventoryComponent::GetEquipmentType(const FName& itemCode)
//{
//	if (inventory.Contains(itemCode))
//	{
//		return inventory[itemCode]->GetEquipmentType();
//	}
//
//	return EEquipmentType::None;
//}
//
//const FEquipmentInformation* UInventoryComponent::GetEquipmentInformation(const FName& itemCode)
//{
//	if (inventory.Contains(itemCode))
//	{
//		return inventory[itemCode]->GetEquipmentInfo();
//	}
//	return nullptr;
//}
