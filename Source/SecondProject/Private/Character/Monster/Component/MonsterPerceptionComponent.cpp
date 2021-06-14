// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Component/MonsterPerceptionComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UMonsterPerceptionComponent::HandleExpiredStimulus(FAIStimulus& StimulusStore)
{
	//현재 Perception에서 인식한 대상들을 가져옶니다.
	TArray<AActor*> out;
	GetKnownPerceivedActors(nullptr, out);

	//그대상 중에 블랙보드가 기억하고 있는 타겟이 있는가 확인함.
	auto target = AIOwner->GetBlackboardComponent()->GetValueAsObject("Target");
	if (target != nullptr)
	{
	//타겟이 있다면, 아직 타겟을 기억하고 있다는 뜻.
		if (out.Contains(target) == false)
		{
			//없다면 타겟을 잊어 버렸다는 뜻.
			AIOwner->GetBlackboardComponent()->SetValueAsObject("Target", nullptr);
		}
	}
}