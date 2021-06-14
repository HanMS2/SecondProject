// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquippableItem/Boots.h"

#include "Character/Player/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Player/Component/InventoryComponent.h"

void ABoots::UseItem(AActor* target)
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
				player->GetBootMesh()->SetSkeletalMesh(info->mesh);
				player->GetinventoryComponent()->SetBoots(info);
			
			}
		}
	}
	Destroy();
}


void ABoots::UnEquip(AActor* target, const FEquipmentInformation* info)
{
	Super::UnEquip(target, info);
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			player->GetinventoryComponent()->SetBoots(nullptr);
			player->GetBootMesh()->SetSkeletalMesh(nullptr);
		}
	}
}

const FEquipmentInformation* ABoots::GetEquippedItem(AActor* target)
{
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			auto equippedItem = player->GetinventoryComponent()->GetEquippedItem();

			return equippedItem.GetBoots();

		}
	}

	return nullptr;
}