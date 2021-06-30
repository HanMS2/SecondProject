// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_StrafeLeft.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UEQC_StrafeLeft : public UEnvQueryContext
{
	GENERATED_BODY()
	
		virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const;
};
