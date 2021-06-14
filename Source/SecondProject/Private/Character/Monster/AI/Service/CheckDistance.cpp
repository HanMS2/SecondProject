// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/AI/Service/CheckDistance.h"
#include "Character/Monster/Controller/MonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCheckDistance::UCheckDistance()
{
	NodeName = "CheckDistance";
	BlackboardKey.SelectedKeyName = "Distance";
}

void UCheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	/*
	* 1. ai��Ʈ�ѷ� ����.
	* 2. ������ ���� Target���� �о��.
	* 3. Target�� AI��Ʈ�ѷ��� �����ϴ� ��� ������ �Ÿ��� ���.(GetDistance�Լ� ���)
	* 4. ����� �Ÿ����� ������ DistanceŰ�� ����.
	*/
	auto AICon = OwnerComp.GetAIOwner();
	
	if (AICon != nullptr)
	{
		auto target = AICon->GetBlackboardComponent()->GetValueAsObject("Target");
		if (target != nullptr)
		{
			auto distance = AICon->GetPawn()->GetDistanceTo(Cast<AActor>(target));
			AICon->GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), distance);
		}
	}
}
