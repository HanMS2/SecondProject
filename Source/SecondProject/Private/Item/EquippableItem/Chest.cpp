// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquippableItem/Chest.h"

#include "Character/Player/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Player/Component/InventoryComponent.h"

void AChest::UseItem(AActor* target)
{
	Super::UseItem(target);

	if (bUnEquipSameEquipment)
	{
		Destroy();
		return;
	}

	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			auto info = GetItemInformation<FEquipmentInformation>();
			if (info != nullptr)
			{
				player->GetChestMesh()->SetSkeletalMesh(info->mesh);
				player->GetinventoryComponent()->SetChest(info);
			}
		}
	}
	Destroy();
}


void AChest::UnEquip(AActor* target, const FEquipmentInformation* info)
{
	Super::UnEquip(target,info);
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			player->GetinventoryComponent()->SetChest(nullptr);
			player->GetChestMesh()->SetSkeletalMesh(nullptr);
		}
	}
}

const FEquipmentInformation* AChest::GetEquippedItem(AActor* target)
{
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			auto equippedItem = player->GetinventoryComponent()->GetEquippedItem();

			return equippedItem.GetChest();

		}
	}

	return nullptr;
}