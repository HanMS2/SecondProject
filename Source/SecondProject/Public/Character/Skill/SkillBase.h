// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameplayTagContainer.h"

#include "SkillBase.generated.h"

/**
 * 이 클래스는 최대한 블루프린트로 작업 가능하게
 * 1.사전 설정 함수
 * 2. 스킬을 사용가능한가
 * 3. 실제로 스킬을 사용
 * 4. 스킬사용을 끝내는 함수
 */
UCLASS(Blueprintable)
class SECONDPROJECT_API USkillBase : public UObject
{
	GENERATED_BODY()
protected:

	UPROPERTY(BlueprintReadOnly)
		class ABaseCharacter* SkillOwner;

	UPROPERTY(EditAnywhere)
		FGameplayTag skillTag;
	UPROPERTY(EditAnywhere)
		class UDataTable* skillTable;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillRequirement> skillRequirement;
	UPROPERTY(EditAnywhere)
		TArray<class UAnimMontage*> skillAnimation;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* skillEffect;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	class UAnimMontage* GetRandomSkillAnimation();

	UFUNCTION(BlueprintCallable)
	virtual	void ApplyDamageEffect(class ABaseCharacter* target);

	UFUNCTION(BlueprintCallable)
		void CreateLineTrace();

	virtual class UWorld* GetWorld()const override;
public:
	const FGameplayTag& GetSkillTag() { return skillTag; }

	void SetSKillOwner(ABaseCharacter* character) { SkillOwner = character; }
public:
	//스킬 사전 설정을 하는 함수.
	UFUNCTION(BlueprintNativeEvent)
	void PreActivateSkill();
	virtual void PreActivateSkill_Implementation();

protected:
	//이 스킬이 사용 가능한지 확인하는 함수입니다. 참이면 사용가능.
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		bool CommitSkill();
	virtual bool CommitSkill_Implementation();

	//실제로 스킬이 작동하는 부분.
	UFUNCTION(BlueprintNativeEvent)
		void ActivateSkill();
	virtual void ActivateSkill_Implementation();

public:
	//이 함수를 호출하면 스킬이 종료됩니다.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void EndSkill();
	virtual void EndSkill_Implementation();	

	template<typename T>
	T* GetSKillInformation();
};

template<typename T>
inline T* USkillBase::GetSKillInformation()
{
	if (skillTable != nullptr)
	{
		return skillTable->FindRow<T>(skillTag.GetTagName(), "");
	}
	return nullptr;
}
