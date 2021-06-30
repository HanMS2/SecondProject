// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_RunEQS.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "ServiceStrafe.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UServiceStrafe : public UBTService_RunEQS
{
	GENERATED_BODY()
protected:

	class AMonsterController* aiCon;

	/** called when search enters underlying branch
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData);

	void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);

};
