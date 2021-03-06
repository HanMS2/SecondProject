// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemActor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/WidgetComponent.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	RootComponent = sphereComponent;
	sphereComponent->SetCollisionProfileName("Item");
	sphereComponent->SetSimulatePhysics(true);
	sphereComponent->SetLinearDamping(10.f);

	particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("particleComp"));
	particleComponent->SetupAttachment(RootComponent);

	widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("widgetComp"));
	widgetComponent->SetupAttachment(RootComponent);
	widgetComponent->SetVisibility(false);

	

}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

