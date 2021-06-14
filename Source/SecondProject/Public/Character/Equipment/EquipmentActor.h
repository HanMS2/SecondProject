// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentActor.generated.h"

UCLASS()
class SECONDPROJECT_API AEquipmentActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipmentActor();

protected:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* skeletalMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	UFUNCTION()
		void OnBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		class UParticleSystem* hitParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* hitSound;

	//�̹� �ѹ� �ǰݴ��� ������ ������ �迭�Դϴ�.
	UPROPERTY()
		TArray<AActor*> hitActors;
public:	

	void AddHitActor(AActor* hitActor);
	void ClearHitActors();

	USkeletalMeshComponent* GetSkeletalMesh() { return skeletalMesh; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//�÷��̾� Ű�� �ش��ϴ� �Լ��� ȣ���� ���Դϴ�.
	virtual void Attack() {};
	virtual void Roll() {};
	virtual void Guard() {};
	virtual bool GuardProcess(const FVector& hitLocation) { return false; }
	virtual void HitProcess(const FVector& hitLocation);
protected:
	class UInventoryComponent* GetInventoryComponent();
	class UStatusComponent* GetStatusComponent();
	float PlayMontage(class UAnimMontage* montage);
	bool isPlayingAnyMontage();

};
