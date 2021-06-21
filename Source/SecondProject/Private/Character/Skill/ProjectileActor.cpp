// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Character/Skill/ProjectileSkillBase.h"


// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComponent"));
	RootComponent = sphereComponent;
	
	particleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("particleSystemComponent"));
	particleSystemComponent->SetupAttachment(RootComponent);
	
	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectileMovementComponent"));
	
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorHit.AddUniqueDynamic(this,&AProjectileActor::OnActorHitEvent);
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileActor::OnActorHitEvent(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (expParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expParticle, GetActorTransform());
	}

	TArray<FHitResult> hits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));

	if (UKismetSystemLibrary::SphereTraceMultiForObjects
		(GetWorld(), OtherActor->GetActorLocation(),
		OtherActor->GetActorLocation() + 1,
		600.f, ObjectTypes,
		false,TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame,
		hits, true))
	{
		for (auto i = 0; i < hits.Num(); i++)
		{
				if (hits[i].GetActor()->IsA<ABaseCharacter>())
				{
					ownerSkill->ApplyDamageEffect(Cast<ABaseCharacter>(hits[i].GetActor()));

				}
		}
	}

	/*
	if (ownerSkill != nullptr)
	{
		if (OtherActor->IsA<ABaseCharacter>())
		{
			ownerSkill->ApplyDamageEffect(Cast<ABaseCharacter>(OtherActor));
		}
	}
	*/
	Destroy();
}
