// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquippableItem/Helmet.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Player/Component/InventoryComponent.h"

void AHelmet::UseItem(AActor* target)
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
				player->GetHelemtMesh()->SetSkeletalMesh(info->mesh);
				player->GetinventoryComponent()->SetHelmet(info);
			}
		}
	}
	Destroy();
}

void AHelmet::UnEquip(AActor* target, const FEquipmentInformation* info)
{
	Super::UnEquip(target,info);
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			player->GetinventoryComponent()->SetHelmet(nullptr);
			player->GetHelemtMesh()->SetSkeletalMesh(nullptr);
		}
	}
}

const FEquipmentInformation* AHelmet::GetEquippedItem(AActor* target)
{
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			auto equippedItem = player->GetinventoryComponent()->GetEquippedItem();

			return equippedItem.GetHelmet();
		
		}
	}

	return nullptr;
}