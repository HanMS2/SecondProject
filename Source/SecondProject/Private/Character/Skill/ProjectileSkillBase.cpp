// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/ProjectileSkillBase.h"
#include "Character/Skill/ProjectileActor.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileActor* UProjectileSkillBase::SpawnProjectile(FName socketName)
{
	if (projectileActorClass != nullptr)
	{
		auto spawnTr = SkillOwner->GetMesh()->GetSocketTransform(socketName);
		auto projectile = GetWorld()->SpawnActor<AProjectileActor>(projectileActorClass.Get(), spawnTr);
	
		projectile->SetSkill(this);
		projectile->GetProjectileMovementComponent()->Velocity = SkillOwner->GetActorForwardVector() * 600.f;
		
		
		return projectile;
	}
	return nullptr;
}

void UProjectileSkillBase::ApplyDamageEffect(ABaseCharacter* target)
{
	Super::ApplyDamageEffect(target);
}
