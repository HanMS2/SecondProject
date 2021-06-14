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

	//������Ʈ�� ���۵� ��,
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	//������Ʈ ����.
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	//������Ʈ�� ���� ��
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);


protected:
	UPROPERTY(EditAnywhere)
		float moveSpeed = 800.f;
};
