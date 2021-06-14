// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/NotifyState/CreateLinetraceAnimNotifyState.h"
#include "Character/BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
void UCreateLinetraceAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != nullptr) {
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (owner != nullptr) {
			owner->hitActors.Empty();
		}
	}
}

void UCreateLinetraceAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp != nullptr) {

		TArray<FHitResult> hits;
		//원형 트레이스를 그리세요. 그려서 걸린 타겟이 있다면, 피해를 주세요.
		if (UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp->GetWorld(),
			MeshComp->GetSocketLocation(startSocket),
			MeshComp->GetSocketLocation(endSocket), radius, objectTypes, false, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, hits, true)) {

	
			for (auto i = 0; i < hits.Num(); i++) {

				if (owner->hitActors.Contains(hits[i].GetActor()) == false) {
					owner->hitActors.AddUnique(hits[i].GetActor());

					hits[i].GetActor()->TakeDamage(10,
						FPointDamageEvent(10, hits[i],
							FVector(),
							UDamageType::StaticClass()),
						Cast<ACharacter>(owner)->GetController(),
						MeshComp->GetOwner());

					if (hitParticle != nullptr) {
						UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), hitParticle, hits[i].Location);
					}
				}
			}

		}
	}
}

void UCreateLinetraceAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != nullptr) {
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (owner != nullptr) {
			owner->hitActors.Empty();
		}
	}
}
