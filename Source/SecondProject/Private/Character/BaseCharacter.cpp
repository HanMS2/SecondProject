// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Character/Component/StatusComponent.h"
#include "Widget/HeadOnHealthBarWidget.h"

#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	statusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("stausComponent"));

	widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("widgetComponent"));
	widgetComponent->SetupAttachment(RootComponent);

	perceptionSourceCopmponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("perceptionSourceCopmponent"));

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateHeadOnHPBarWidget();
	OnDeath.AddUniqueDynamic(this, &ABaseCharacter::setSpectator);
	OnDeath.AddUniqueDynamic(this, &ABaseCharacter::SetRagDoll);

}

void ABaseCharacter::UpdateHeadOnHPBarWidget()
{
	if (widgetComponent->GetUserWidgetObject() != nullptr) {
		UHeadOnHealthBarWidget* headOnWidget = 
			Cast<UHeadOnHealthBarWidget>(widgetComponent->GetUserWidgetObject());
		if (headOnWidget != nullptr) {
			headOnWidget->SetHPPercent(statusComponent->GetHPPercent());
		}
	}

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	statusComponent->SetHP(statusComponent->GetHP() - (int32)DamageAmount);
	UpdateHeadOnHPBarWidget();
	return 0.0f;
}

void ABaseCharacter::setSpectator()
{
	GetCapsuleComponent()->SetCollisionProfileName("Ragdoll");

}

void ABaseCharacter::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

}

void ABaseCharacter::SetRagDoll()
{
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);
}

void ABaseCharacter::HPBarRemove()
{
	widgetComponent->SetVisibility(false);
}

