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
	1. Ÿ�ٰ� , ���� ������ Yaw���� ���սô�.
	2. ���� Yaw���� �����ڰ� ���� ���ϵ��� ���� ��Ĩ�ô�. <-�󤤽��� ������ �������� ���� - 180 ~ 0, �������� 0 ~ 180;
	
	
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

		//���� -180 ~ -60 ������ ��쿡 , �������� ȸ����Ŵ.
		if (yaw >= -180 && yaw < -60)
		{
			auto time = mon->GetMesh()->GetAnimInstance()->Montage_Play(LeftTurnMontage);

			//Ÿ�̸ӷ� Turn �Լ� ��ȣ�� ����.
			FTimerHandle turnTimerHandle;
			mon->GetWorldTimerManager().SetTimer(turnTimerHandle,this,&UTask_Turn::Turn,time);
		}
		//���� 60 ~ 180 ������ ��쿡 , ���������� ȸ����Ŵ.
		else if (yaw >= 60 && yaw <= 180)
		{
			auto time = mon->GetMesh()->GetAnimInstance()->Montage_Play(rightTurnMontage);

			//Ÿ�̸ӷ� Turn �Լ� ��ȣ�� ����.
			FTimerHandle turnTimerHandle;
			mon->GetWorldTimerManager().SetTimer(turnTimerHandle, this, &UTask_Turn::Turn, time);
		}
		//���� -60 ~ 60 ������ ��쿡 , ���� ƽ ȸ���� ��Ű�� ��.
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
