// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Monster.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Character/Component/StatusComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Monster/Controller/MonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Player/Controller/CustomController.h"

AMonster::AMonster() {
	GetCapsuleComponent()->SetCollisionProfileName("Monster");
//	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	//aimoveTo Task 사용시 이동을 보간함.
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SetGenericTeamId(FGenericTeamId(1));
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	OnDeath.AddUniqueDynamic(this, &AMonster::DropItem);
	OnDeath.AddUniqueDynamic(this, &AMonster::RemoveBossWidget);
}

void AMonster::DropItem()
{
	if (dropTable != nullptr)
	{
		TArray<const FDropTable*> dropitems;
		dropTable->GetAllRows("", dropitems);

		float sum = 0;
		for (auto value : dropitems)
		{
			sum += value->percent;
			if (sum > 100)
			{
				return;
			}
		}
		auto dropCount = FMath::RandRange(1, 5);
		for (auto i = 0; i < dropCount; i++)
		{
			auto percent = FMath::RandRange(0.f, 100.f);
			auto perCheck = 0.f;
			
			for (auto j = 0; j < dropitems.Num(); j++)
			{
				perCheck += dropitems[j]->percent;
				if (percent <= perCheck)
				{
					auto spawnTr = FTransform(GetActorLocation() + FMath::RandPointInBox(FBox(FVector(1, 1, 0), FVector(10, 10, 0))));

					auto spawndItem = UGameplayStatics::BeginDeferredActorSpawnFromClass
					(GetWorld(), dropitems[j]->item.Get(),
						spawnTr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

					UGameplayStatics::FinishSpawningActor(spawndItem, spawnTr);
					break;
				}
			}

			
		}
		
		/*
		auto dropCount = FMath::RandRange(1, 5);

		for (auto i = 0; i < dropCount; i++)
		{
			auto dropItemIndex = FMath::RandRange(0, dropitems.Num() - 1);
			
			auto spawnTr = FTransform(GetActorLocation() + FMath::RandPointInBox(FBox(FVector(1, 1, 0), FVector(10, 10, 0))));


			auto spawndItem = UGameplayStatics::BeginDeferredActorSpawnFromClass
			(GetWorld(), dropitems[dropItemIndex]->item.Get(),
				spawnTr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

			UGameplayStatics::FinishSpawningActor(spawndItem, spawnTr);

		}
		*/
	}
}

void AMonster::OnChangeMoveStateEvent(EAIMoveState newState)
{
	switch (newState)
	{
	case EAIMoveState::WALK:
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		break;

	case EAIMoveState::RUN:
		GetCharacterMovement()->MaxWalkSpeed = 900.f;
		break;
	default:
		break;
	}

}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (statusComponent->GetHP() <= 0)
	{
		//여기에 경험치 주는 함수 ㄱㄱ
		OnDeath.Broadcast();
	}


	return 0.0f;
}

void AMonster::RemoveBossWidget()
{
	if (bBoss == true)
	{


		auto aicon = Cast<AMonsterController>(GetController());
		if (aicon != nullptr)
		{
			auto target = aicon->GetBlackboardComponent()->GetValueAsObject("Target");

			if (target != nullptr)
			{
				auto con = Cast<ACustomController>(Cast<ACharacter>(target)->GetController());
				if (con != nullptr)
				{
					con->RemoveBossWidget();
				}
			}
		}
	}

}
void AMonster::SetPhysicsAssetBodyCollsionResponse(FName BoneName, EBodyCollisionResponse::Type response)
{
	for (auto i = 0; i < GetMesh()->GetPhysicsAsset()->SkeletalBodySetups.Num(); i++) {
		if (GetMesh()->GetPhysicsAsset()->SkeletalBodySetups[i]->BoneName.IsEqual(BoneName)) {
			GetMesh()->GetPhysicsAsset()->SkeletalBodySetups[i]->CollisionReponse = response;
			break;
		}
	}
}