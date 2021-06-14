// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/LockOnComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Monster/Monster.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/Player/Controller/CustomController.h"

#include "Blueprint/UserWidget.h"


// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	player =  Cast<APlayerCharacter>(GetOwner());
	controller = Cast<ACustomController>(player->GetController());
}

void ULockOnComponent::CreateCameraTrace()
{
	if (player != nullptr) {
		auto camera = player->GetFollowCamera();
		if (camera != nullptr) {

			TArray<FHitResult> hits;
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));

			//ī�޶� �������� n��ŭ���� Ʈ���̽��� �׸�.
			if (UKismetSystemLibrary::SphereTraceMultiForObjects(
				this,
				camera->GetComponentLocation(),
				//ī�޶� �� n��ŭ�� ������ ��� 
				//ī�޶� ��ġ, ī�޶� �� �������(camera->GetForwardVector())
				//������� : (0,0,0)�� �������� �ִ� (1,1,1)������ ���Ⱚ
				(camera->GetForwardVector() * distance) + camera->GetComponentLocation(),
				radius,
				ObjectTypes,
				false,
				TArray<AActor*>(),
				EDrawDebugTrace::ForOneFrame,
				hits, true)) {
				//Ʈ���̽��� �ɸ� ������ ����.
				for (auto i = 0; i < hits.Num(); i++) {
					if (LockOnableMonsters.Contains(hits[i].GetActor()) == false) {
						LockOnableMonsters.Emplace(Cast<AMonster>(hits[i].GetActor()));
					}
				}
				//����� ������ �Ÿ������� �����ؼ�, ���� ����� ����� lockOnTarget�� ������ �մϴ�.
		
			}
			else {
				if (LockOnableMonsters.Num() == 0) {
					StopLockOn();
				}
			}

			if (lockOnTarget == nullptr) {
				lockOnTarget = FindNearestTarget();
			}


		}
	}
}

void ULockOnComponent::LookAtTarget()
{
	if (lockOnTarget != nullptr) {
		//�÷��̾�ĳ���Ͱ� lockOnTarget�� �ٶ󺸰� ����.
		//�� ����(�÷��̾�,lockOnTarget)������ ������ ����.
		FRotator rot = (lockOnTarget->GetActorLocation() - player->GetActorLocation()).Rotation();
		rot.Pitch = player->GetActorRotation().Pitch;
		rot.Roll = player->GetActorRotation().Roll;

		if (controller != nullptr) {

			if (bBlockLookAt == false) {
				player->SetActorRotation(rot);
				controller->SetControlRotation(rot);
			}

			controller->SetLockOnWidgetPos(lockOnTarget);

		}
		player->GetCameraBoom()->SetWorldRotation(rot);
	}
}

class AMonster* ULockOnComponent::FindNearestTarget()
{
	if (LockOnableMonsters.Num() > 0) {
		auto nearTarget = LockOnableMonsters[0];
		for (auto i = 0; i < LockOnableMonsters.Num(); i++) {

			float dis = LockOnableMonsters[i]->GetDistanceTo(player);
			if (dis < nearTarget->GetDistanceTo(player)) {
				nearTarget = LockOnableMonsters[i];
			}

		}
		return nearTarget;
	}

	return nullptr;
}

void ULockOnComponent::CheckDistanceToPlayer()
{
	if (player != nullptr) {

		for (auto i = 0; i < LockOnableMonsters.Num(); i++) {
			auto monster = LockOnableMonsters[i];
			if (monster != nullptr) {
				if (monster->GetDistanceTo(player) > 1200.f) {
					LockOnableMonsters.RemoveAt(i);
				}
			}
		}


		if (lockOnTarget != nullptr) {
			if (lockOnTarget->GetDistanceTo(player) > 1200.f) {
				player->LockOn();
				lockOnTarget = nullptr;
			}
		}
	}
}

void ULockOnComponent::NextLockOnTarget()
{
	curIndex = curIndex + 1;

	if (LockOnableMonsters.IsValidIndex(curIndex)) {
		lockOnTarget = LockOnableMonsters[curIndex];
	}
	else {

		curIndex = 0;

		if (LockOnableMonsters.IsValidIndex(curIndex)) {
		
			lockOnTarget = LockOnableMonsters[curIndex];
		}
		else {
			player->LockOn();
		}

	}
}

void ULockOnComponent::PreLockOnTarget()
{
	curIndex = curIndex - 1;

	if (LockOnableMonsters.IsValidIndex(curIndex)) {
		lockOnTarget = LockOnableMonsters[curIndex];
	}
	else {
		curIndex = LockOnableMonsters.Num() - 1;

		if (LockOnableMonsters.IsValidIndex(curIndex)) {
			lockOnTarget = LockOnableMonsters[curIndex];
		}
		else {
			player->LockOn();
		}
	}
}


// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bLockOn) {
		//ī�޶� Ʈ���̽��� ����.
		CreateCameraTrace();

		//Ÿ���� �ٶ�.
		LookAtTarget();


		CheckDistanceToPlayer();
	}
}

void ULockOnComponent::SetLockOn()
{
	bLockOn = true;

	player->GetCameraBoom()->bUsePawnControlRotation = false;
	player->GetCameraBoom()->bEnableCameraLag = true;
	player->GetCameraBoom()->bEnableCameraRotationLag = true;

	player->GetCameraBoom()->CameraLagSpeed = 200;

	if (controller != nullptr) {
		controller->SetVisibilityLockOnWidget(ESlateVisibility::Visible);
	}
}

void ULockOnComponent::StopLockOn()
{
	bLockOn = false;

	player->GetCameraBoom()->bUsePawnControlRotation = true;
	player->GetCameraBoom()->bEnableCameraLag = false;
	player->GetCameraBoom()->bEnableCameraRotationLag = false;

	if (controller != nullptr) {
		controller->SetVisibilityLockOnWidget(ESlateVisibility::Hidden);
	}

	lockOnTarget = nullptr;
	LockOnableMonsters.Empty();
}

