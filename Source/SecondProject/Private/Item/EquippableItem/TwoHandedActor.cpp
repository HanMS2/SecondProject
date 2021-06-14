// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EquippableItem/TwoHandedActor.h"
#include "..\..\..\Public\Item\EquippableItem\TwoHandedActor.h"

#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/Component/InventoryComponent.h"
#include "Character/Component/StatusComponent.h"
#include "Kismet/GameplayStatics.h"


void ATwoHandedActor::Attack()
{
	auto invenComp = GetInventoryComponent();

	if (invenComp != nullptr)
	{
		auto equipInfo = invenComp->GetEquippedItem();

		if (equipInfo.GetWeapon() != nullptr)
		{
			auto player = Cast<APlayerCharacter>(GetOwner());
			if (player != nullptr)
			{

				if (player->bReadyCombat == false) {
					if (equipInfo.GetWeapon()->EquipMontage != nullptr)
					{
						if (player->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == false)
						{
							player->GetMesh()->GetAnimInstance()->Montage_Play(equipInfo.GetWeapon()->EquipMontage);
							player->bReadyCombat = true;
						}
					}
				}
				else
				{
					player->bAttack = true;
					
					if (GetStatusComponent()->CheckStamina(equipInfo.GetWeapon()->attackSP)
						&& player->bReadyCombat && player->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == false)
					{
						GetStatusComponent()->PauseRecoverStaminaPerTime();
						GetStatusComponent()->SetSP(GetStatusComponent()->GetSP() - equipInfo.GetWeapon()->attackSP);
						PlayMontage(equipInfo.GetWeapon()->AttackMontage);
					}
				}
			}
		}
	}
}

void ATwoHandedActor::Roll()
{

	auto invenComp = GetInventoryComponent();
	if (invenComp != nullptr)
	{
		auto equipInfo = invenComp->GetEquippedItem();
		if (equipInfo.GetWeapon() != nullptr)
		{
			if (GetStatusComponent()->CheckStamina(equipInfo.GetWeapon()->rollSP))
			{
				GetStatusComponent()->PauseRecoverStaminaPerTime();
				GetStatusComponent()->SetSP(GetStatusComponent()->GetSP() - equipInfo.GetWeapon()->rollSP);
				float time = PlayMontage(equipInfo.GetWeapon()->RollMontage);
				FTimerHandle rollTimerHandle;
				
				GetWorldTimerManager().SetTimer(rollTimerHandle, GetStatusComponent(), &UStatusComponent::ResumeRecoverStaminaPerTime, time);

			}
		}
	}

}

void ATwoHandedActor::Guard()
{
	auto invenComp = GetInventoryComponent();
	
	if (invenComp != nullptr)
	{
		auto equipInfo = invenComp->GetEquippedItem();
		if (equipInfo.GetWeapon() != nullptr)
		{
			auto player = Cast<APlayerCharacter>(GetOwner());
			if (player != nullptr)
			{
				player->bGuard = true;
				float time = PlayMontage(equipInfo.GetWeapon()->guardMontage);
				FTimerDelegate guardTimerDel = FTimerDelegate::CreateUObject(player, &APlayerCharacter::SetGuard, false);
				FTimerHandle guardTimerHandle;
				GetWorldTimerManager().SetTimer(guardTimerHandle, guardTimerDel,time,false);
			}

			Cast<APlayerCharacter>(GetOwner())->bGuard = !Cast<APlayerCharacter>(GetOwner())->bGuard;
			float time = PlayMontage(equipInfo.GetWeapon()->guardMontage);
			FTimerHandle guardTimerHandle;

			GetWorldTimerManager().SetTimer(guardTimerHandle, GetStatusComponent(), &UStatusComponent::ResumeRecoverStaminaPerTime, time);

			
		}
	}

}

bool ATwoHandedActor::GuardProcess(const FVector& hitLocation)
{
	auto invenComp = GetInventoryComponent();
	if (invenComp != nullptr)
	{
		auto equipInfo = invenComp->GetEquippedItem();
		if (equipInfo.GetWeapon() == nullptr)
		{
			return false;
		}


		auto mesh = Cast<APlayerCharacter>(GetOwner())->GetMesh();
		//1.hitLocation 과 플레이어 사이의 각도.
		FRotator rot = (hitLocation - GetActorLocation()).Rotation();
		//1번 각도랑, 현재 플레이어의 로테이션을 이용하면, 좌 우 를 알수 있음.
		float yaw = (rot - GetActorRotation()).Yaw;

		//알아보기 쉽게 한번 가공함.
		if (yaw > 180) {
			yaw -= 360;
		}
		else if (yaw < -180) {
			yaw += 360;
		}

		//플레이어의 앞을 기준으로
		//좌측값 : -180 ~ 0
		//우측값 : 0 ~ 180


		//좌측
		if (-120 <= yaw && yaw < 120) {
			if (equipInfo.GetWeapon()->leftGuardMontage != nullptr)
			{
				//좌측 가드 몽타주 재생
				mesh->GetAnimInstance()->Montage_Play(equipInfo.GetWeapon()->leftGuardMontage);
			}
			else
			{
				mesh->GetAnimInstance()->Montage_Play(equipInfo.GetWeapon()->frontGuardMontage);
			}
		}

		else {
			if (equipInfo.GetWeapon()->gotHit_BackMontage != nullptr)
			{
				mesh->GetAnimInstance()->Montage_Play(equipInfo.GetWeapon()->gotHit_BackMontage);
			}
			if (equipInfo.GetWeapon()->gotHitParticle != nullptr) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), equipInfo.GetWeapon()->gotHitParticle, hitLocation);
			}
			return false;
		}

		if (equipInfo.GetWeapon()->GuardParticle != nullptr) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), equipInfo.GetWeapon()->GuardParticle, hitLocation);
		}
	}


	return true;
}

void ATwoHandedActor::HitProcess(const FVector& hitLocation)
{
	Super::HitProcess(hitLocation);
}
