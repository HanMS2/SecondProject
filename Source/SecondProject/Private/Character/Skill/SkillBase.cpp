// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/SkillBase.h"
#include "Character/Skill/SkillRequirement.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/BaseCharacter.h"
#include "Character/Monster/Monster.h"
#include "Kismet/GameplayStatics.h"
UAnimMontage* USkillBase::GetRandomSkillAnimation()
{
	if (skillAnimation.Num() == 0)
	{
		return nullptr;
	}

	return skillAnimation[FMath::RandRange(0, skillAnimation.Num() - 1)];

}

void USkillBase::ApplyDamageEffect(ABaseCharacter* target)
{
	const auto req = skillRequirement.GetDefaultObject();
	if (req != nullptr)
	{
		req->ApplyDamageEffect(target);
		
	}
}

void USkillBase::CreateLineTrace()
{
	TArray<FHitResult> hits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));

	if (UKismetSystemLibrary::SphereTraceMultiForObjects(
		SkillOwner, SkillOwner->GetActorLocation(),
		SkillOwner->GetActorForwardVector() * 500.f + SkillOwner->GetActorLocation(),
		100.f, ObjectTypes,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame,
		hits, true))
	{
		for (auto i = 0; i < hits.Num(); i++)
		{
			if (hits[i].GetActor()->IsA<AMonster>())
			{
				ApplyDamageEffect(Cast<ABaseCharacter>(hits[i].GetActor()));
			}
		}
	}
}

UWorld* USkillBase::GetWorld() const
{
	if (SkillOwner != nullptr)
	{
		return	SkillOwner->GetWorld();
	}
	return nullptr;
	
}

void USkillBase::PreActivateSkill_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("PreActivateSkill_Implementation"));

	ActivateSkill();
}

bool USkillBase::CommitSkill_Implementation()
{
	const auto req = skillRequirement.GetDefaultObject();
	if (req != nullptr)
	{	
		req->SetSKillOwner(SkillOwner);
		//발동 가능하면 참이 리턴됩니다.
		bool bCanActivate = req->CheckSkillCost();
		return bCanActivate;
	}
	
	
	return false;
}

void USkillBase::ActivateSkill_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("ActivateSkill_Implementation"));
	if (CommitSkill())
	{
		//스킬 코스트를 적용시킵니다.
		const auto req = skillRequirement.GetDefaultObject();
		if (req != nullptr)
		{
			req->SetSKillOwner(SkillOwner);
			req->ApplyCost();
		}
		if (SkillOwner != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), skillEffect,
				SkillOwner->GetActorForwardVector() * 500.f + SkillOwner->GetActorLocation(),
				FRotator::ZeroRotator);
		}		
	}
}

void USkillBase::EndSkill_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("EndSkill_Implementation"));
}
