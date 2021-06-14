// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/AI/Service/FindPlayer.h"


#include "Character/Monster/Controller/MonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Monster/Monster.h"
#include "Kismet/KismetSystemLibrary.h"


void UFindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FHitResult hit;


	//1.���� Ʈ���̽��� �ϴ� �÷��̾ ����.
	auto AICon = OwnerComp.GetAIOwner();


	if (UKismetSystemLibrary::SphereTraceSingleForObjects(AICon->GetWorld(),
		AICon->GetPawn()->GetActorLocation(), AICon->GetPawn()->GetActorLocation() + 1,
		radius, objectType, false, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, hit, true))
	{

		TArray < TEnumAsByte<EObjectTypeQuery>> objType;

		objType.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		objType.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		FHitResult outHit;
		//2.������ �÷��̾�� ���� ���̿� �ƹ��͵� ������ (����Ʈ���̽�), �÷��̾ �ν��ߴ�. �������.
		if (UKismetSystemLibrary::LineTraceSingleForObjects(AICon->GetWorld(), AICon->GetPawn()->GetActorLocation(),
			hit.GetActor()->GetActorLocation(), objType, false, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, outHit, true) == false)
		{
			AICon->GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), hit.GetActor());
		}
	}
}