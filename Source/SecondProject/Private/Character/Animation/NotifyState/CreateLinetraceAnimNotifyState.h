// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CreateLinetraceAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class UCreateLinetraceAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	UPROPERTY()
		class ABaseCharacter* owner;

	//������Ʈ�� ���۵� ��,
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	//������Ʈ ����.
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	//������Ʈ�� ���� ��
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere)
		TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	UPROPERTY(EditAnywhere)
		FName startSocket;
	UPROPERTY(EditAnywhere)
		FName endSocket;
	UPROPERTY(EditAnywhere)
		float radius;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* hitParticle;
};
