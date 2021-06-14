// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Controller/MonsterController.h"

#include "Character/Monster/Monster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/Controller/CustomController.h"
#include "Perception/AISense_Sight.h"
#include "Character/Monster/Component/MonsterPerceptionComponent.h"

AMonsterController::AMonsterController()
{
	PerceptionComponent = CreateDefaultSubobject<UMonsterPerceptionComponent>(TEXT("PerceptionComponent"));
	
}


void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);



	OwnerMonster = Cast<AMonster>(InPawn);
	auto baseChar = Cast<ABaseCharacter>(InPawn);

	if (OwnerMonster != nullptr)
	{
	OnChangeMoveState.AddUniqueDynamic(OwnerMonster, &AMonster::OnChangeMoveStateEvent);
	OwnerMonster->OnDeath.AddUniqueDynamic(this, &AMonsterController::StopBehaviorTree);
	OwnerMonster->OnDeath.AddUniqueDynamic(baseChar, &ABaseCharacter::HPBarRemove);
	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AMonsterController::OnTargetPerceptionUpdatedEvent);
		if (OwnerMonster->AITree != nullptr)
		{
			RunBehaviorTree(OwnerMonster->AITree);

			if (OwnerMonster->patrolLocation_A != nullptr)
			{
				GetBlackboardComponent()->SetValueAsVector("PatrolA", OwnerMonster->patrolLocation_A->GetActorLocation());
			}

			if (OwnerMonster->patrolLocation_B != nullptr)
			{
				GetBlackboardComponent()->SetValueAsVector("PatrolB", OwnerMonster->patrolLocation_B->GetActorLocation());
			}

		}
	}

}

void AMonsterController::StopBehaviorTree()
{
	BrainComponent->StopLogic("Death");

}

void AMonsterController::OnTargetPerceptionUpdatedEvent(AActor* actor, FAIStimulus Stimulus)
{
		
	//UE_LOG(LogTemp, Log, TEXT("11111111111111111111"));
	
	if (actor->IsA<APlayerCharacter>())
	{
		auto player = Cast<APlayerCharacter>(actor);
		auto controller = Cast<ACustomController>(player->GetController());
		
		if (controller != nullptr)
		{
			if (Cast<AMonster>(GetPawn())->bBoss == true)
			{
				controller->AddBossWidget(Cast<AMonster>(GetPawn()));
			}
		}		


		playerActor = actor;		
	}	
}

void AMonsterController::Tick(float DeltaTime)
{
	/*
	Super::Tick(DeltaTime);
	

	if (playerActor != nullptr)
	{
		TArray< AActor*> OutActors;
		PerceptionComponent->GetKnownPerceivedActors(UAISense_Sight::StaticClass(), OutActors);


		if (OutActors.Num() == 0)
		{
			GetBlackboardComponent()->SetValueAsObject("Target", nullptr);
			playerActor = nullptr;
		}
		else
		{
			if (OutActors.Contains(playerActor))
			{
				GetBlackboardComponent()->SetValueAsObject("Target", playerActor);
			}
		}

		//UE_LOG(LogTemp, Log, TEXT("Tick 돈다."));
	}
	*/
}

