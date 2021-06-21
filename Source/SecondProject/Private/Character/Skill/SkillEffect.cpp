// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/SkillEffect.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/StatusComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Component/SkillComponent.h"

void USkillEffect::ApplySkillEffect(ABaseCharacter* target, class ABaseCharacter* causer)
{
	if (target != nullptr)
	{
		auto statComp = target->GetStatusComponent();

		switch (effectedStatType)
		{
		case EEffectedStat::HP:
			if (bDamage == false)
			{
				statComp->SetHP(statComp->GetHP() - value);
			}
			else
			{
				target->TakeDamage(value,FDamageEvent(), causer->GetController(),causer);
				UGameplayStatics::SpawnEmitterAtLocation(target->GetWorld(), damagedParicle, target->GetActorTransform());
			}
			
				break;
		case EEffectedStat::SP:
			statComp->SetHP(statComp->GetSP() - value);
				break;
		case EEffectedStat::MP:
			statComp->SetHP(statComp->GetMP() - value);
				break;
		case EEffectedStat::COOLDOWN:
		{
			target->GetSkillComponent()->AddSkillEffect(effectTag);
			FTimerHandle coolDownTimerHandle;
			FTimerDelegate coolDownTimerDel = FTimerDelegate::CreateUObject(this, &USkillEffect::EndSkillEffect, target);
			target->GetWorldTimerManager().SetTimer(coolDownTimerHandle, coolDownTimerDel, value, false);
		}
				break;
		default:
				break;
		}
	}
}

void USkillEffect::EndSkillEffect(ABaseCharacter* target)
{
	if (target != nullptr)
	{
		target->GetSkillComponent()->RemoveEffectTag(effectTag);
	}	

}
