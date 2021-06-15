// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Equipment,
	Consume,

};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Weapon,
	Shield,

};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	Weapon,
	Shield,
	Helmet,
	Gloves,
	Chest,
	Legs,
	Boots,
	None,
};

USTRUCT(BlueprintType)
//언리얼에서 구조체를 쓸경우 F를 붙여주자.
struct FItemInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FName item_Code;
	UPROPERTY(EditAnywhere)
		TSubclassOf <class AItemActor> itemClass;
	UPROPERTY(EditAnywhere)
		FName item_Name;

	UPROPERTY(EditAnywhere)
		class UTexture2D* item_Image;

	UPROPERTY(EditAnywhere)
		FName item_Description;

	UPROPERTY(EditAnywhere)
		FName item_Description_Long;

	UPROPERTY(EditAnywhere)
		EItemType item_Type;

	UPROPERTY(EditAnywhere)
		int32 sellPrice;
};


USTRUCT(BlueprintType)
struct FEquipmentInformation : public FItemInformation
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		EEquipmentType equipmentType;
	UPROPERTY(EditAnywhere)
		float damage;
	UPROPERTY(EditAnywhere)
		float def;
	UPROPERTY(EditAnywhere)
		class USkeletalMesh* mesh;
};


USTRUCT(BlueprintType)
struct FPotionInformation : public FItemInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float hp;
	UPROPERTY(EditAnywhere)
		float sp;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* useParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* useSound;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* useMontage;
};	
USTRUCT(BlueprintType)
struct FWeaponInformation : public FEquipmentInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEquipmentActor> sqawnableEquipmentClass;

	UPROPERTY(EditAnywhere)
		EWeaponType weaponType;

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* newMesh;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* EquipMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* UnEquipMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere)
		float attackSP;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* RollMontage;
	UPROPERTY(EditAnywhere)
		float rollSP;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* gotHit_CenterMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* gotHit_RightMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* gotHit_LeftMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* gotHit_BackMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* guardMontage;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* leftGuardMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* rightGuardMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* frontGuardMontage;
	


	UPROPERTY(EditAnywhere)
		class UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* gotHitParticle;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* GuardParticle;

	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* animBP;

};


UCLASS()
class SECONDPROJECT_API UItemTypes : public UObject
{
	GENERATED_BODY()
	
		

};
