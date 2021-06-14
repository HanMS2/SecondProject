// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GenericTeamAgentInterface.h"

#include "BaseCharacter.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class SECONDPROJECT_API ABaseCharacter : public ACharacter,public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UStatusComponent* statusComponent;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UWidgetComponent* widgetComponent;
public:
	class UStatusComponent* GetStatusComponent() { return statusComponent; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UAIPerceptionStimuliSourceComponent* perceptionSourceCopmponent;

	void UpdateHeadOnHPBarWidget();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/**
	 * Apply damage to this actor.
	 * @see https://www.unrealengine.com/blog/damage-in-ue4
	 * @param DamageAmount		How much damage to apply
	 * @param DamageEvent		Data package that fully describes the damage received.
	 * @param EventInstigator	The Controller responsible for the damage.
	 * @param DamageCauser		The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	 * @return					The amount of damage actually applied.
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY()
		TArray<AActor*> hitActors;

	FOnDeath OnDeath;
	UFUNCTION()
		void setSpectator();
	virtual void OnConstruction(const FTransform& transform);

	UFUNCTION()
		void SetRagDoll();
	UFUNCTION()
		void HPBarRemove();

protected:
	FGenericTeamId myTeam;
	/** Assigns Team Agent to given TeamID */
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) { myTeam = TeamID; }
public:

	/** Retrieve team identifier in form of FGenericTeamId */
	virtual FGenericTeamId GetGenericTeamId() const { return myTeam; }

};
