// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon.h"
#include "Character/Player/PlayerCharacter.h"
#include "Item/ItemActor.h"
#include "Character/Equipment/EquipmentActor.h"
#include "Character/Player/Component/InventoryComponent.h"

void AWeapon::UseItem(AActor* target)
{

	Super::UseItem(target);


	auto player = Cast<APlayerCharacter>(target);
	if (player != nullptr)
	{
		if (bUnEquipSameEquipment)
		{
			if (player->GetSpawndWeapon() != nullptr)
			{
				player->GetSpawndWeapon()->Destroy();
			}
			Destroy();
			return;
		}

		auto info = GetItemInformation<FWeaponInformation>();
		if (info != nullptr)
		{
			if (player->GetSpawndWeapon() != nullptr)
			{
				player->GetSpawndWeapon()->Destroy();
			}
			auto weapon = GetWorld()->SpawnActor<AEquipmentActor>(info->sqawnableEquipmentClass.Get());
			if (weapon != nullptr)
			{
				weapon->SetOwner(target);
				weapon->GetSkeletalMesh()->SetSkeletalMesh(info->newMesh);
				weapon->AttachToComponent(player->GetMesh(),
					FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false),
					"WeaponBackSocket");

				player->GetinventoryComponent()->SetWeapon(info);
				player->GetMesh()->SetAnimInstanceClass(info->animBP->GetAnimBlueprintGeneratedClass());
				player->SetSpawndWeapon(weapon);
			}
		}


		/*
		auto weapon = player->GetSpawndWeapon();
		if (weapon != nullptr)
		{
			auto info = GetItemInformation<FWeaponInformation>();
			if(info != nullptr)
			{
				weapon->GetSkeletalMesh()->SetSkeletalMesh(info->newMesh);
				weapon->AttachToComponent(player->GetMesh(),
					FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false),
					"WeaponBackSocket");

				player->GetinventoryComponent()->SetWeapon(info);

				player->GetMesh()->SetAnimInstanceClass(info->animBP->GetAnimBlueprintGeneratedClass());
			}
		}
		*/
	}
	Destroy();
}

void AWeapon::UnEquip(AActor* target, const FEquipmentInformation* info)
{
	Super::UnEquip(target,info);
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			player->GetinventoryComponent()->SetWeapon(nullptr);
			player->GetWeapon()->Destroy();
		}
	}
}

const FEquipmentInformation* AWeapon::GetEquippedItem(AActor* target)
{
	if (target != nullptr)
	{
		auto player = Cast<APlayerCharacter>(target);
		if (player != nullptr)
		{
			auto equippedItem = player->GetinventoryComponent()->GetEquippedItem();

			return equippedItem.GetWeapon();

		}
	}

	return nullptr;
}
