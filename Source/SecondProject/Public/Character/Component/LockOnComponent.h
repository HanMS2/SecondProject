// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"


/*
	�÷��̾� ĳ������ ī�޶� ������.
	ī�޶�κ��� n��ŭ�� �Ÿ����� Ʈ���̽��� ��(���� Ʈ���̽�)
	Ʈ���̽��� ���� �ɸ���(����) ī�޶��, ĳ���Ͱ� ���͸� �ٶ󺸰� ����.
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECONDPROJECT_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULockOnComponent();

protected:

	bool bLockOn;
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		class APlayerCharacter* player;
	UPROPERTY()
		class ACustomController* controller;
	UPROPERTY()
		TArray<class AMonster*> LockOnableMonsters;

	UPROPERTY()
		class AMonster* lockOnTarget;

	UPROPERTY()
		int32 curIndex = 0;

	void CreateCameraTrace();
	void LookAtTarget();
	class AMonster* FindNearestTarget();
	//���� ������ ����� �÷��̾������ �Ÿ��� ƽ���� ����ؼ�, �ʹ� �ָ� ��������, ����������Ŵ.
	void CheckDistanceToPlayer();


public:	
	//�迭�� ����Ǿ��ִ� ���� ����� ������ Ÿ������ ��.
	void NextLockOnTarget();
	//�迭�� ����Ǿ� �ִ� ���� ����� ������ Ÿ������ ��.
	void PreLockOnTarget();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void SetLockOn();
	void StopLockOn();

		

	UPROPERTY(EditAnywhere)
		float distance;
	UPROPERTY(EditAnywhere)
		float radius;

	bool bBlockLookAt = false;
};
