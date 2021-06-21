// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameplayTagContainer.h"

#include "SkillBase.generated.h"

/**
 * �� Ŭ������ �ִ��� �������Ʈ�� �۾� �����ϰ�
 * 1.���� ���� �Լ�
 * 2. ��ų�� ��밡���Ѱ�
 * 3. ������ ��ų�� ���
 * 4. ��ų����� ������ �Լ�
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
	//��ų ���� ������ �ϴ� �Լ�.
	UFUNCTION(BlueprintNativeEvent)
	void PreActivateSkill();
	virtual void PreActivateSkill_Implementation();

protected:
	//�� ��ų�� ��� �������� Ȯ���ϴ� �Լ��Դϴ�. ���̸� ��밡��.
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		bool CommitSkill();
	virtual bool CommitSkill_Implementation();

	//������ ��ų�� �۵��ϴ� �κ�.
	UFUNCTION(BlueprintNativeEvent)
		void ActivateSkill();
	virtual void ActivateSkill_Implementation();

public:
	//�� �Լ��� ȣ���ϸ� ��ų�� ����˴ϴ�.
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
