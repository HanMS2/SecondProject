// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECONDPROJECT_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float HP;
	UPROPERTY(EditAnywhere)
		float MaxHP = 100;
	UPROPERTY(EditAnywhere)
		float SP;
	UPROPERTY(EditAnywhere)
		float MaxSP = 100;
	UPROPERTY(EditAnywhere)
		float AttackSpeed = 1.f;

	UPROPERTY(EditAnywhere)
		float dam;
	UPROPERTY(EditAnywhere)
		float def;

//
//
//	FTimerHandle recoverStaminaTimerHandle;
//	FTimerHandle removeStaminaTimerHandle;
//
//	void RecoverStamina();
//	void RemoveStamina();
//public:
//	void PauseRecoverStamina();
//
//	void RunRemoveStaminaTimer();
//
//	void PauseRemoveStamina();
//	void RunRecoverStaminaTimer();


	//n�ʴ� sp�� ȸ����Ű�� Ÿ�̸� �ڵ�

	//sp ȸ������ ��û�� ������ �����մϴ�.
	TArray<int32>PauseStaminaOrder;

public:

	void AddDam(float value) { dam += value; }
	void AddDef(float value) { def += value; }

	const float& GetDam() { return dam; }
	const float& GetDef() { return def; }


	FTimerHandle recoverStaminaTimeTimerHandle;

	void RecoverStamina(float value);
	void RemoveStamina(float value);
	void PauseRecoverStaminaPerTime();
	void ResumeRecoverStaminaPerTime();

	void RecoverStaminaPerTime(float value);

public:	

	const float& GetHP() { return HP; }
	const float& GetMaxHP() { return MaxHP; }
	const float& GetSP() { return SP; }
	const float& GetMaxSP() { return MaxSP; }

	const float GetHPPercent() { return HP / (float)MaxHP; }
	const float GetSPPercent() { return SP / (float)MaxSP; }

	void SetHP(float value);
	void SetSP(float value);
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//���̸� ����� sp�� ����.
	bool CheckStamina(float value);



};
