// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillRequirement.generated.h"

/**
 * ��� �Լ��� ȣ���ϵ� 
 * SetSkillOwner �Լ��� SkillOwner�� �����Ǿ���Ѵ�.
 */
UCLASS(Blueprintable)
class SECONDPROJECT_API USkillRequirement : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class ABaseCharacter* SkillOwner;

	//��ų �ڽ�Ʈ
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> skillCost;

	//��ų ��Ÿ��
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> skillCoolDown;

	//��ų ���� ����Ʈ
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> skillDamageEffect;

public:
	//�ݵ�� ���Լ��� ������� �ҷ����� �մϴ�.
	void SetSKillOwner(ABaseCharacter* character) {SkillOwner = character;}
	bool CheckSkillCost();
	void ApplyCost();
	void ApplyDamageEffect(ABaseCharacter* target);
};
