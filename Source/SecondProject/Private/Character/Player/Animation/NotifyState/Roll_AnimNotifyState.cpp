// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/NotifyState/Roll_AnimNotifyState.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Component/LockOnComponent.h"


#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

void URoll_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != nullptr) {
		player = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (player != nullptr) {
			//player->DisableInput(Cast<APlayerController>(player->GetController()));
			player->GetCharacterMovement()->RotationRate = FRotator(0, -1, 0);
		}
	}
}

void URoll_AnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp != nullptr) {
		if (player != nullptr) {

			auto movement = player->GetCharacterMovement();
			movement->Velocity = player->GetActorForwardVector() * moveSpeed;

		}

	}
}

void URoll_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != nullptr) {
		if (player != nullptr) {
			player->GetLockOnComponent()->bBlockLookAt = false;
			player->GetCharacterMovement()->RotationRate = player->originalRotationRate;
		}
	}
}
