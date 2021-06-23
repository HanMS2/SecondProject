// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LoadingInstance.generated.h"

/**
 * 
 */
UCLASS()
class SECONDPROJECT_API ULoadingInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> loadingWidgetClass;

	virtual void Init();

	UFUNCTION()
		void StartLoadingScreen(const FString& levelName);


};
