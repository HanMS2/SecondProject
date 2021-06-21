// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/SkillBase.h"
#include "ProjectileSkillBase.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UProjectileSkillBase : public USkillBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectileActor> projectileActorClass;

	UFUNCTION(BlueprintCallable)
		class AProjectileActor* SpawnProjectile(FName socketName);

public:
	virtual	void ApplyDamageEffect(class ABaseCharacter* target) override;

};
