// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "MonsterPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UMonsterPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

protected:
		/** @note no need to call super implementation, it's there just for some validity checking */
		virtual void HandleExpiredStimulus(FAIStimulus& StimulusStore)override;

	
};
