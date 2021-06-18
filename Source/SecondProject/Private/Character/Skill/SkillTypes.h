// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "SkillTypes.generated.h"


USTRUCT(BlueprintType)
//�𸮾󿡼� ����ü�� ����� F�� �ٿ�����.
struct FSkillInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillBase> skillClass;
	
	UPROPERTY(EditAnywhere)
		class UImage* skill_Image;

	UPROPERTY(EditAnywhere)
		FName skill_Name;

};

USTRUCT(BlueprintType)
struct FStoredSKill : public FTableRowBase
{
	GENERATED_BODY()

private:
	FSkillInformation* skill_Info;
public:
	const FSkillInformation* GetSkillInfo() { return skill_Info; }
	void SetSkillInfo(FSkillInformation* info) { skill_Info = info; }

	
};
/**
 * 
 */
UCLASS()
class USkillTypes : public UObject
{
	GENERATED_BODY()
	
};
