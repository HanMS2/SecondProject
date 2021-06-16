// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/StatusComponent.h"
#include "TimerManager.h"
#include "Character/Player/PlayerCharacter.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	

}


void UStatusComponent::RecoverStamina(float value)
{
	SP = FMath::Clamp(SP + value, 0.0f, MaxSP);

}

void UStatusComponent::RemoveStamina(float value)
{
	SP = FMath::Clamp(SP - value, 0.0f, MaxSP);
}

void UStatusComponent::PauseRecoverStaminaPerTime()
{
	PauseStaminaOrder.Push(0);
	
	if (GetWorld()->GetTimerManager().IsTimerActive(recoverStaminaTimeTimerHandle) == true)
	{
		GetWorld()->GetTimerManager().PauseTimer(recoverStaminaTimeTimerHandle);
	}

}

void UStatusComponent::ResumeRecoverStaminaPerTime()
{
	if (PauseStaminaOrder.Num() > 0)
	{
		PauseStaminaOrder.Pop();
	}
	if (PauseStaminaOrder.Num() == 0)
	{
		GetWorld()->GetTimerManager().UnPauseTimer(recoverStaminaTimeTimerHandle);
	}

}

void UStatusComponent::RecoverStaminaPerTime(float value)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(recoverStaminaTimeTimerHandle) == false)
	{
		FTimerDelegate recoverStaminaTimerDel = FTimerDelegate::CreateUObject(this, &UStatusComponent::RecoverStamina, value);
		GetWorld()->GetTimerManager().SetTimer(recoverStaminaTimeTimerHandle, recoverStaminaTimerDel, 0.3f, true);
	}

}

void UStatusComponent::SetHP(float value)
{
	HP = FMath::Clamp(value, 0.0f, MaxHP);
}

void UStatusComponent::SetSP(float value)
{
	SP = FMath::Clamp(value, 0.0f, MaxSP);
}

//// Called every frame
//void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

bool UStatusComponent::CheckStamina(float value)
{
	if (SP > value) {
		return true;
	}
	return false;
}

void UStatusComponent::AddEXP(const int32& exp)
{
	curExp += exp;
	if (levelUpTable != nullptr)
	{
		auto info = levelUpTable->FindRow<FLevelUpInformation>(FName(*FString::FormatAsNumber(level)),"");
		if (info != nullptr)
		{
			if (curExp >= info->exp)
			{
				UE_LOG(LogTemp, Log, TEXT("level up : %d"), level);
				level++;
			}

		}
	}

}

