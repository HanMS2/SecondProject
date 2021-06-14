// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquippableItem/Gloves.h"

#include "Character/Player/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Player/Component/InventoryComponent.h"

void AGloves::UseItem(AActor* target)
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
				player->GetGloveMesh()->SetSkeletalMesh(info->mesh);
				player->GetinventoryComponent()->SetGlove(info);
			}
		}
	}
	Destroy();
}


void AGloves::UnEquip(AActor* target, const FEquipmentInformation* info)
{
	Super::UnEquip(target,info);
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			player->GetinventoryComponent()->SetGlove(nullptr);
			player->GetGloveMesh()->SetSkeletalMesh(nullptr);
		}
	}
}

const FEquipmentInformation* AGloves::GetEquippedItem(AActor* target)
{
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			auto equippedItem = player->GetinventoryComponent()->GetEquippedItem();

			return equippedItem.GetGlove();

		}
	}

	return nullptr;
}