// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "StatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeGold, const int32&, changedGold);

USTRUCT(BlueprintType)
struct FLevelUpInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	//(현재 레벨 +1) 로 올라가기 위한 경험치
	UPROPERTY(EditAnywhere)
		float exp;
};


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
		int32 level = 1;

	UPROPERTY(EditAnywhere)
		float HP;
	UPROPERTY(EditAnywhere)
		float MaxHP = 100;
	UPROPERTY(EditAnywhere)
		float MP;
	UPROPERTY(EditAnywhere)
		float MaxMP;
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
TArray<int32>PauseStaminaOrder;

	UPROPERTY(EditAnywhere)
		int32 gold;

	UPROPERTY(EditAnywhere)
		int32 curExp;
	UPROPERTY(EditAnywhere)
		class UDataTable* levelUpTable;


public:

	void AddDam(float value) { dam += value; }
	void AddDef(float value) { def += value; }

	const float& GetDam() { return dam; }
	const float& GetDef() { return def; }

	const int32& GetGold() { return gold; }
	void SetGold(const int32& value) { gold = value; OnChangeGold.Broadcast(gold); }

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
	const float& GetMP() { return MP; }
	const float& GetMaxMP() { return MaxMP; }

	const float GetHPPercent() { return HP / (float)MaxHP; }
	const float GetSPPercent() { return SP / (float)MaxSP; }

	void SetHP(float value);
	void SetSP(float value);
	void SetMP(float value) { MP = value; }
	void SetMaxMP(float value) { MaxMP = value; }
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//참이면 충분히 sp가 있음.
	bool CheckStamina(float value);


	FOnChangeGold OnChangeGold;

	UFUNCTION(BlueprintCallable)
	void AddEXP(const int32& exp);
};
