// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Component/MonsterPerceptionComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UMonsterPerceptionComponent::HandleExpiredStimulus(FAIStimulus& StimulusStore)
{
	//���� Perception���� �ν��� ������ �������ϴ�.
	TArray<AActor*> out;
	GetKnownPerceivedActors(nullptr, out);

	//�״�� �߿� �����尡 ����ϰ� �ִ� Ÿ���� �ִ°� Ȯ����.
	auto target = AIOwner->GetBlackboardComponent()->GetValueAsObject("Target");
	if (target != nullptr)
	{
	//Ÿ���� �ִٸ�, ���� Ÿ���� ����ϰ� �ִٴ� ��.
		if (out.Contains(target) == false)
		{
			//���ٸ� Ÿ���� �ؾ� ���ȴٴ� ��.
			AIOwner->GetBlackboardComponent()->SetValueAsObject("Target", nullptr);
		}
	}
}