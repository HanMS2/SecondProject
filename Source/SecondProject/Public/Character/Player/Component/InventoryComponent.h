// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Item/ItemTypes.h"

#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FStoredItem
{

	GENERATED_BODY()
private:
	FItemInformation* info;
public:
	int32 item_Count = 0;

	FStoredItem() {}
	FStoredItem(FItemInformation* itemInfo, const int32 count)
	{
		info = itemInfo;
		item_Count = count;
	}
	const FItemInformation* GetItemInfo() { return info; }
	const FEquipmentInformation* GetEquipmentInfo() { return (FEquipmentInformation*)info; }

	const bool IsEquipment()
	{
		return info->item_Type == EItemType::Equipment;
	}


	//geteq 사용전, 반드시 isEquipment가 참인지 확이;ㄴ행햐 합니다.
	const EEquipmentType GetEquipmentType()
	{
		if (IsEquipment() == true)
		{

			auto equip = (FEquipmentInformation*)info;

			if (equip != nullptr)
			{
				return equip->equipmentType;
			}
		}

		return EEquipmentType::None;
	}

};


USTRUCT(BlueprintType)
struct FEquipedItem
{
	GENERATED_BODY()
private:
	FWeaponInformation* weapon;
	FEquipmentInformation* shield;


	FEquipmentInformation* helmet;
	FEquipmentInformation* chest;
	FEquipmentInformation* glove;
	FEquipmentInformation* leg;
	FEquipmentInformation* boots;

public:
	void SetWeapon(FWeaponInformation* info) { weapon = info; }
	void SetShield(FEquipmentInformation* info) { shield = info; }
	
	void SetHelmet(FEquipmentInformation* info) { helmet = info; }
	void SetChest(FEquipmentInformation* info) { chest = info; }
	void SetGlove(FEquipmentInformation* info) { glove = info; }
	void SetLeg(FEquipmentInformation* info) { leg = info; }
	void SetBoots(FEquipmentInformation* info) { boots = info; }
	
	const FEquipmentInformation* GetHelmet() { return helmet; }
	const FEquipmentInformation* GetChest()	 { return chest;}
	const FEquipmentInformation* GetGlove()	 { return glove; }
	const FEquipmentInformation* GetLeg()	 { return leg;  }
	const FEquipmentInformation* GetBoots()	 { return boots; }
	
	
	const FWeaponInformation* GetWeapon() { return weapon; }
	const FEquipmentInformation* GetShield() { return shield; }


};

//Delegate는 함수를 저장하는 변수

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquip, class UStatusComponent*, statComp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnEquip, class UStatusComponent*, statComp);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAddQuick, class UTexture2D*, image, const int32&, count);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUseQuick, const int32&, count);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECONDPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TMap<FName, FStoredItem*> inventory;
	FEquipedItem equippedItem;
	
	TArray<FName> quickSlot;

	int32 quickIndex = 0;
	bool existQuickItem();
public:	
	
	void Removequick(const FName& itemCode);

	void AddQuick(const FName& itemCode,const int32& index);
	void AddItem(class AItemActor* item);
		
	const TMap<FName, FStoredItem*>& GetInventory() { return inventory; }
	
	void UseItem(const FName itemCode, AActor* target);

	void DropItem(const FName itemCode);
	
	void RemoveItem(const FName itemCode);

	const FStoredItem* GetItem(const FName& itemCode);
	const FItemInformation* GetItemInfo(const FName& itemCode);
	void SetWeapon(FWeaponInformation* info) { equippedItem.SetWeapon(info); }
	void SetShield(FEquipmentInformation* info) { equippedItem.SetShield(info); }

	void SetHelmet(FEquipmentInformation* info) { equippedItem.SetHelmet(info); }
	void SetChest(FEquipmentInformation* info)  { equippedItem.SetChest(info); }
	void SetGlove(FEquipmentInformation* info)  { equippedItem.SetGlove(info); }
	void SetLeg(FEquipmentInformation* info)	{ equippedItem.SetLeg(info); }
	void SetBoots(FEquipmentInformation* info)  { equippedItem.SetBoots(info); }

	const FEquipedItem& GetEquippedItem() { return equippedItem; }

	//const EEquipmentType GetEquipmentType(const FName& itemCode);
	
	//const FEquipmentInformation* GetEquipmentInformation(const FName& itemCode);

	void QuickUp();
	void QuickDown();
	void UseQuick();


	FEquip EquipEvent;
	
	FUnEquip UnEquipEvent;

	FAddQuick AddQuickEvent;

	FUseQuick UseQuickEvent;
};
