// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Roll_AnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API URoll_AnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()


	class APlayerCharacter* player;

	//스테이트가 시작될 때,
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	//스테이트 구간.
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	//스테이트가 끝날 때
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);


protected:
	UPROPERTY(EditAnywhere)
		float moveSpeed = 800.f;
};
