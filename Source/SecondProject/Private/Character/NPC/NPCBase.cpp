// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/NPCBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Widget/NPC/NPCDialogWidget.h"
#include "Character/Player/Controller/CustomController.h"

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCollisionProfileName("NPC");
	CapsuleComponent->InitCapsuleSize(50.0f, 100.0f);
	RootComponent = CapsuleComponent;
	SkeletalMeshComponent =CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_MeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}

const TArray<FNPCSellItem*> ANPCBase::GetSellItemList()
{
	if (sellTable != nullptr)
	{
		TArray<FNPCSellItem*> items;
		sellTable->GetAllRows<FNPCSellItem>("", items);
		return items;
	}

	return TArray<FNPCSellItem*>();
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ANPCBase::Interaction(APlayerController* controller)
{
	auto con = Cast<ACustomController>(controller);
	
	if (con != nullptr)
	{
		if (con->GetDialogWidget() == nullptr)
		{
			con->SetDialogWidget(CreateWidget<UNPCDialogWidget>(con, dialogWidgetClass.Get()));
		}
		if (con->GetDialogWidget()->IsInViewport() == false)
		{
			con->GetDialogWidget()->Init(this);
			con->GetDialogWidget()->AddToViewport();
		}
	}
}

