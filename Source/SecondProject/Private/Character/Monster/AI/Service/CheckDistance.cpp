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
	* 1. ai컨트롤러 들고옴.
	* 2. 블랙보드 안의 Target값을 읽어옴.
	* 3. Target과 AI컨트롤러가 조종하는 대상 사이의 거리를 계산.(GetDistance함수 사용)
	* 4. 계산한 거리값을 블랙보드 Distance키에 저장.
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
