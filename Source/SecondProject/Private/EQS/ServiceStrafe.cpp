// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/ServiceStrafe.h"

#include "Character/Monster/Controller/MonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"


void UServiceStrafe::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
	
	aiCon = Cast<AMonsterController>(SearchData.OwnerComp.GetAIOwner());

	auto target = Cast<AActor>(aiCon->GetBlackboardComponent()->GetValueAsObject("Target"));
	if (target != nullptr)
	{
		aiCon->SetFocus(target);
		aiCon->GetPawn()->bUseControllerRotationYaw = true;
	}

	QueryFinishedDelegate.BindUObject(this, &UServiceStrafe::OnQueryFinished);
}

void UServiceStrafe::OnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	if (Result->IsSuccsessful())
	{
		aiCon->MoveToLocation(Result->GetItemAsLocation(0), 20.f, true, true, true);
	}

}
