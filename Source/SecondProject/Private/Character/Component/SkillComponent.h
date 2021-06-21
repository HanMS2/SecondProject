// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Skill/SkillTypes.h"
#include "GameplayTagContainer.h"

#include "SkillComponent.generated.h"

UCLASS()
class USkillComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	USkillComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	TMap<struct FGameplayTag, struct FStoredSKill> skillMap;

	TArray<struct FGameplayTag> skillEffectList;
public:
	UFUNCTION(BlueprintCallable)
	void GiveSkill(TSubclassOf<class USkillBase> skillClass);

	UFUNCTION(BlueprintCallable)
	void UseSkill(FGameplayTag skillTag);
	
	UFUNCTION(BlueprintCallable)
	void AddSkillEffect(FGameplayTag effectTag);
	UFUNCTION(BlueprintCallable)
		bool ExistEffect(FGameplayTag effectTag);

	void RemoveEffectTag(FGameplayTag effectTag);



};
