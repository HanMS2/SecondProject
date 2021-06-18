// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillEffect.generated.h"

UENUM(BlueprintType)
enum class EEffectedStat : uint8
{
	HP,
	SP,
	MP,
};

/**
 * 
 */
UCLASS(Blueprintable)
class SECONDPROJECT_API USkillEffect : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		EEffectedStat effectedStatType;
	UPROPERTY(EditAnywhere)
		float value;
	UPROPERTY(EditAnywhere)
		bool bDamage = false;
	UPROPERTY(EditAnywhere,meta = (EditCondition = "bDamage"))
		class UParticleSystem* damagedParicle;
public:
	virtual void ApplySkillEffect(class ABaseCharacter* target, class ABaseCharacter* causer = nullptr);

	EEffectedStat GetEffectedStat() { return effectedStatType; }
	const float GetValue() { return value; }

};
