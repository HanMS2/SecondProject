// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/SkillComponent.h"
#include "Character/Skill/SkillBase.h"

// Sets default values
ASkillComponent::ASkillComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkillComponent::GiveSkill(TSubclassOf<class USkillBase> skillClass)
{
	if (skillClass != nullptr)
	{
		const auto skill = skillClass.GetDefaultObject();

		if (skill != nullptr)
		{
			if (skillMap.Contains(skill->GetSkillTag()) == false)
			{

				/*
				FStoredSKill newSkill;
				newSkill.SetSkillInfo(*skill->GetSKillInformation<FSkillInformation>());
				skillMap.Add(skill->GetSkillTag(), newSkill);
			*/
			}
		}
	}
}

void ASkillComponent::UseSkill(FGameplayTag skillTag)
{
	if (skillMap.Contains(skillTag))
	{
		const auto skill = skillMap[skillTag].GetSkillInfo()->skillClass.GetDefaultObject();
		skill->PreActivateSkill();

	}
}

