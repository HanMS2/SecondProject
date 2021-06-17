// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/SkillBase.h"

void USkillBase::PreActivateSkill_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("PreActivateSkill_Implementation"));
}

bool USkillBase::CommitSkill_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("CommitSkill_Implementation"));
	return false;
}

void USkillBase::ActivateSkill_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("ActivateSkill_Implementation"));
}

void USkillBase::EndSkill_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("EndSkill_Implementation"));
}
