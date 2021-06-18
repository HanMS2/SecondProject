// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/SkillRequirement.h"

#include "Character/Skill/SkillEffect.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/StatusComponent.h"


bool USkillRequirement::CheckSkillCost()
{
	if (SkillOwner != nullptr)
	{
		auto statComp = SkillOwner->GetStatusComponent();

		const auto cost = skillCost.GetDefaultObject();
		if (cost != nullptr)
		{
			const auto value = cost->GetValue();
			switch (cost->GetEffectedStat())
			{
			case EEffectedStat::SP:
				return statComp->GetSP() > value;
				break;
			case EEffectedStat::HP:
				return statComp->GetHP() > value;
				break;
			case EEffectedStat::MP:
				return statComp->GetMP() > value;
				break;
			}
		}
	}
	return false;
}

void USkillRequirement::ApplyCost()
{
	if (SkillOwner != nullptr)
	{
		const auto cost = skillCost.GetDefaultObject();
		cost->ApplySkillEffect(SkillOwner);
	}
}

void USkillRequirement::ApplyDamageEffect(ABaseCharacter* target)
{
	if (target != nullptr)
	{
		if (skillDamageEffect != nullptr)
		{
			const auto damageEffect = skillDamageEffect.GetDefaultObject();
			damageEffect->ApplySkillEffect(target, SkillOwner);
		}
	}
}
