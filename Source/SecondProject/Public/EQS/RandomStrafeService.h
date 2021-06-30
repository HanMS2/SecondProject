// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"

#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "RandomStrafeService.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API URandomStrafeService : public UBTService_BlackboardBase
{
	GENERATED_BODY()
protected:

		UPROPERTY(EditAnywhere)
		TArray<class UEnvQuery*> queries;


	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//���񽺰� ���۵ɋ� �ѹ� ȣ��˴ϴ�.
	/** called when search enters underlying branch
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	//virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	//Evq�� �������� ȣ��˴ϴ�.
	void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);

	UPROPERTY()
		class AMonsterController* aiCon;
	UPROPERTY()
		class UEnvQuery* randQuery;
};
