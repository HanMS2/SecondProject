// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/AI/Task/Task_Turn.h"

#include "Character/Monster/Monster.h"
#include "Character/Monster/Controller/MonsterController.h"
#include "Character/Player/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UTask_Turn::UTask_Turn()
{
	NodeName = "Turn";
	BlackboardKey.SelectedKeyName = "Target";

	bNotifyTick = true;
}

void UTask_Turn::Turn()
{
	/*
	1. 타겟과 , 몬스터 사이의 Yaw값을 구합시다.
	2. 구한 Yaw값을 개발자가 보기 편하도록 값을 고칩시다. <-몬ㄴ스터 정면을 기준으로 왼쪽 - 180 ~ 0, 오른쪽이 0 ~ 180;
	
	
	*/
	if (target != nullptr && monster != nullptr)
	{
		auto mon = Cast<AMonster>(monster);
		auto yaw = ((target->GetActorLocation() - mon->GetActorLocation()).Rotation() - mon->GetActorRotation()).Yaw;

		if (yaw > 180)
		{
			yaw -= 360;
		}else if(yaw < -180)
		{
			yaw += 360;
		}

		//좌측 -180 ~ -60 사이일 경우에 , 왼쪽으로 회전시킴.
		if (yaw >= -180 && yaw < -60)
		{
			auto time = mon->GetMesh()->GetAnimInstance()->Montage_Play(LeftTurnMontage);

			//타이머로 Turn 함수 재호출 하자.
			FTimerHandle turnTimerHandle;
			mon->GetWorldTimerManager().SetTimer(turnTimerHandle,this,&UTask_Turn::Turn,time);
		}
		//우측 60 ~ 180 사이일 경우에 , 오른쪽으로 회전시킴.
		else if (yaw >= 60 && yaw <= 180)
		{
			auto time = mon->GetMesh()->GetAnimInstance()->Montage_Play(rightTurnMontage);

			//타이머로 Turn 함수 재호출 하자.
			FTimerHandle turnTimerHandle;
			mon->GetWorldTimerManager().SetTimer(turnTimerHandle, this, &UTask_Turn::Turn, time);
		}
		//정면 -60 ~ 60 사이일 경우에 , 기존 틱 회전을 시키게 함.
		else  //if(yaw >= -60 && yaw <= 60)
		{
			bActiveTick = true;
		}
	}
}

void UTask_Turn::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bActiveTick)
	{

		if (target != nullptr && monster != nullptr)
		{
			FRotator targetRot = (target->GetActorLocation() - monster->GetActorLocation()).Rotation();
			targetRot.Pitch = monster->GetActorRotation().Pitch;
			targetRot.Roll = monster->GetActorRotation().Roll;


			auto lerpRot = FMath::RInterpTo(monster->GetActorRotation(), targetRot, DeltaSeconds, interpSpeed);

			monster->SetActorRotation(lerpRot);

			if (FMath::Abs(targetRot.Yaw - lerpRot.Yaw) <= AcceptSize)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}
}

EBTNodeResult::Type UTask_Turn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto aiCon = OwnerComp.GetAIOwner();
	if (aiCon != nullptr)
	{
		bActiveTick = false;
		monster = aiCon->GetPawn();
		target =  Cast<AActor>(aiCon->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

		if (bUseTurnAnim == false)
		{
			bActiveTick = true;
		}
		else
		{
			Turn();
		}


		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}
