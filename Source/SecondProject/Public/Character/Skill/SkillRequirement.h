// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillRequirement.generated.h"

/**
 * 어떠한 함수를 호출하든 
 * SetSkillOwner 함수로 SkillOwner가 설정되어야한다.
 */
UCLASS(Blueprintable)
class SECONDPROJECT_API USkillRequirement : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class ABaseCharacter* SkillOwner;

	//스킬 코스트
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> skillCost;

	//스킬 쿨타임
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> skillCoolDown;

	//스킬 피해 이펙트
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> skillDamageEffect;

public:
	//반드시 이함수가 가장먼저 불러져야 합니다.
	void SetSKillOwner(ABaseCharacter* character) {SkillOwner = character;}
	bool CheckSkillCost();
	void ApplyCost();
	void ApplyDamageEffect(ABaseCharacter* target);
};
