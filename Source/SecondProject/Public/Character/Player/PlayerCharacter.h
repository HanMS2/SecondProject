// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:

	APlayerCharacter();

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

protected:
	UPROPERTY(VisibleAnywhere)
		class ULockOnComponent* lockOnComponent;
public:

	class ULockOnComponent* GetLockOnComponent() { return lockOnComponent; }

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	FRotator originalRotationRate = FRotator(0.0f, 540.0f, 0.0f);

protected:

	UPROPERTY(BlueprintReadOnly)
		float moveForward;
	UPROPERTY(BlueprintReadOnly)
		float moveRight;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	virtual void AddControllerYawInput(float Val) override;
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEquipmentActor> equipmentClass;

protected:
	void SpawnEquipment();

	UPROPERTY()
		AEquipmentActor* spawndWeapon;
	UPROPERTY()
		AEquipmentActor* spawndShield;

	
	void EquipWeapon();

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AttackMontage;

	void Attack();
	void StopAttack();

	//공격키를 누르면 참이 됨.
public:
	AEquipmentActor* GetSpawndWeapon() { return spawndWeapon; }
	void SetSpawndWeapon(AEquipmentActor* newWeapon) { spawndWeapon = newWeapon; }
	AEquipmentActor* GetSpawndShield() { return spawndShield; }

	bool GetbAttack() {	return bAttack;	}

	void Run();
	void StopRun();
protected:
	UPROPERTY(BlueprintReadOnly)
		bool bRun;


	//요 액터가 생성(혹은 게임시작)되면 한번 호출되는 함수입니다.
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
		class UAnimMontage* RollMontage;

	FTimerHandle RollStaminaTimerHandle;

	void Roll();



	void Guard();




	UPROPERTY(BlueprintReadOnly)
		bool bLockOn;


	FTimerHandle nextLockOnTargetTimerHandle;
	FTimerHandle preLockOnTargetTimerHandle;


	UPROPERTY(EditAnywhere)
		class UParticleSystem* guardParticle;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* gotHitParticle;

	bool GuardProcess(FVector hitLocation);
	void HitProcess(FVector hitLocation);

	void QuickUp();
	void QuickDown();
	void UseQuick();
public:
	void LockOn();
	bool GetLockOn() { return bLockOn; }


	AEquipmentActor* GetWeapon() { return spawndWeapon; }
	AEquipmentActor* GetShield() { return spawndShield; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWidgetComponent> damageWidgetComponentClass;

public:
	void ShowDamage(float damage, FVector hitLocation);

	void OpenInventory();

protected:
	UPROPERTY(VisibleAnywhere)
		class UInventoryComponent* inventoryComponent;


	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OnEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

	void PickUp();

	UPROPERTY()
		FTimerHandle RunStaminaTimerHandle;

	UPROPERTY()
		class AItemActor* pickUPItem = nullptr;
	
	public:
	class UInventoryComponent* GetinventoryComponent();

	UPROPERTY(BlueprintReadOnly)
		bool bReadyCombat = false;


	UPROPERTY(BlueprintReadOnly)
		bool bGuard;

	bool bAttack = false;
	void SetGuard(bool value) { bGuard = value; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* Helmet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* Glove;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* Chest;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* Leg;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* Boot;

	virtual void OnConstruction(const FTransform& Transform) override;

	public:
		class USkeletalMeshComponent* GetHelemtMesh() { return Helmet; }
		class USkeletalMeshComponent* GetChestMesh()  { return Chest; }
		class USkeletalMeshComponent* GetGloveMesh()  { return Glove; }
		class USkeletalMeshComponent* GetLegMesh()	  { return Leg; }
		class USkeletalMeshComponent* GetBootMesh()   { return Boot; }


};
