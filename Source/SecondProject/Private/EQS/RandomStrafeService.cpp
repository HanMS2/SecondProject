// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/RandomStrafeService.h"

#include "EQS/RandomStrafeService.h"
#include "Character/Monster/Controller/MonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "EnvironmentQuery/EnvQueryManager.h"

void URandomStrafeService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (randQuery) {
		FEnvQueryRequest(randQuery, aiCon->GetPawn()).Execute(EEnvQueryRunMode::RandomBest5Pct, this, &URandomStrafeService::OnQueryFinished);
	}
}

void URandomStrafeService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	aiCon = Cast<AMonsterController>(SearchData.OwnerComp.GetAIOwner());
	auto target = Cast<AActor>(aiCon->GetBlackboardComponent()->GetValueAsObject("Target"));
	aiCon->SetFocus(target);
	aiCon->GetPawn()->bUseControllerRotationYaw = true;

	randQuery = queries[FMath::RandRange(0, queries.Num() - 1)];
}

void URandomStrafeService::OnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	if (Result->IsSuccsessful()) {
		aiCon->MoveToLocation(Result->GetItemAsLocation(0), 50.f);
	}
}


