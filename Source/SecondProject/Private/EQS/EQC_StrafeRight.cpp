// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/EQC_StrafeRight.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

#include "Character/Monster/Controller/MonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Monster/Monster.h"

void UEQC_StrafeRight::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	auto querier = QueryInstance.Owner.Get();
	if (querier != nullptr)
	{
		AActor* querierActor = Cast<AActor>(querier);
		if (querierActor != nullptr)
		{
			auto aiCon = Cast<AMonsterController>(Cast<AMonster>(querierActor)->GetController());

			if (aiCon != nullptr)
			{
				auto target = Cast<AActor>(aiCon->GetBlackboardComponent()->GetValueAsObject("target"));

				if (target != nullptr)
				{
					auto rot = (querierActor->GetActorLocation() - target->GetActorLocation()).Rotation();
					auto result = FRotator(0, rot.Yaw + 90, 0);


					UEnvQueryItemType_Point::SetContextHelper(ContextData,
						(result.Vector() * 300) + querierActor->GetActorLocation());
				}
			}
		}
	}
}
