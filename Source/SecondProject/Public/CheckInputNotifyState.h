// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CheckInputNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UCheckInputNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		class APlayerCharacter* Player;

	bool bContine;

	UPROPERTY(EditAnywhere)
		FName nextSection;


	virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload);
	virtual void BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime);
	virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload);

};
