// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/SkillComponent.h"
#include "Character/Skill/SkillBase.h"

// Sets default values
USkillComponent::USkillComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void USkillComponent::GiveSkill(TSubclassOf<class USkillBase> skillClass)
{
	if (skillClass != nullptr)
	{
		const auto skill = skillClass.GetDefaultObject();

		if (skill != nullptr)
		{
			if (skillMap.Contains(skill->GetSkillTag()) == false)
			{

				
				FStoredSKill newSkill;
				newSkill.SetSkillInfo(skill->GetSKillInformation<FSkillInformation>());
				skillMap.Add(skill->GetSkillTag(), newSkill);
			
			}
		}
	}
}

void USkillComponent::UseSkill(FGameplayTag skillTag)
{
	if (skillMap.Contains(skillTag))
	{
		const auto skill = skillMap[skillTag].GetSkillInfo()->skillClass.GetDefaultObject();
		skill->SetSKillOwner(Cast<ABaseCharacter>(GetOwner()));
		skill->PreActivateSkill();

	}
}

