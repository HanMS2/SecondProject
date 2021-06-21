// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

UCLASS()
class SECONDPROJECT_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* sphereComponent;
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* particleSystemComponent;
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* projectileMovementComponent;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* expParticle;

	class UProjectileSkillBase* ownerSkill;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UProjectileMovementComponent* GetProjectileMovementComponent() { return projectileMovementComponent; }
	//AActor, OnActorHit, AActor*, SelfActor, AActor*, OtherActor, FVector, NormalImpulse, const FHitResult&, Hit );
	
	UFUNCTION()
		void OnActorHitEvent(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void SetSkill(class UProjectileSkillBase* skill) { ownerSkill = skill; }
};
