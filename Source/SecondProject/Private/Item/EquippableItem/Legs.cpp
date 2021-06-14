// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquippableItem/Legs.h"

#include "Character/Player/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Player/Component/InventoryComponent.h"

void ALegs::UseItem(AActor* target)
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
				player->GetLegMesh()->SetSkeletalMesh(info->mesh);
				player->GetinventoryComponent()->SetLeg(info);
			}
		}
	}
	Destroy();
}

void ALegs::UnEquip(AActor* target, const FEquipmentInformation* info)
{
	Super::UnEquip(target,info);
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			player->GetinventoryComponent()->SetLeg(nullptr);
			player->GetLegMesh()->SetSkeletalMesh(nullptr);
		}
	}
}

const FEquipmentInformation* ALegs::GetEquippedItem(AActor* target)
{
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			auto equippedItem = player->GetinventoryComponent()->GetEquippedItem();

			return equippedItem.GetLeg();

		}
	}

	return nullptr;
}