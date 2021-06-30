// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_StrafeRight.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API UEQC_StrafeRight : public UEnvQueryContext
{
	GENERATED_BODY()

		virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const;
};
