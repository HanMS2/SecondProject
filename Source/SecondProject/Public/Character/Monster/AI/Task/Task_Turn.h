// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_Turn.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UTask_Turn : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

		UPROPERTY()
		class AActor* target;
	UPROPERTY()
		class AActor* monster;


public:

	UTask_Turn();

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere)
		float AcceptSize = 10;
	UPROPERTY(EditAnywhere)
		float interpSpeed = 10;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseTurnAnim"))
		class UAnimMontage* rightTurnMontage;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseTurnAnim"))
		class UAnimMontage* LeftTurnMontage;

	UPROPERTY(EditAnywhere)
		bool bUseTurnAnim = false;

protected:
	UPROPERTY(EditAnywhere)
		bool bActiveTick = false;

	void Turn();
};
