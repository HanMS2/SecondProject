// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/Monster.h"
#include "DesertDragon.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API ADesertDragon : public AMonster
{
	GENERATED_BODY()


		ADesertDragon();
public:
	
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;



};
