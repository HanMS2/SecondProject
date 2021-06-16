// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/NPCBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Widget/NPC/NPCDialogWidget.h"
#include "Character/Player/Controller/CustomController.h"
#include "Item/ItemActor.h"
#include "Character/Player/Component/InventoryComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Component/StatusComponent.h"

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
	for (auto item : GetSellItemList())
	{
		sellItemList.Emplace(*item);
	}
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

void ANPCBase::BuyItem(class APlayerCharacter* player, const FName& itemCode)
{
	for (auto& sellItem : sellItemList)
	{
		const auto item = sellItem.sellItemClass.GetDefaultObject();
		if (item->GetItemInformation<FItemInformation>()->item_Code.IsEqual(itemCode))
		{
			if (sellItem.count > 0)
			{
				//플레이어가 들고있는 골드량을 체크
				if (player->GetStatusComponent()->GetGold() - sellItem.price >= 0)
				{
					auto spawnItem = GetWorld()->SpawnActor<AItemActor>(item->GetClass());
					if (spawnItem)
					{
						spawnItem->SetActorHiddenInGame(true);
						player->GetinventoryComponent()->AddItem(spawnItem);
						spawnItem->Destroy();
					}
					player->GetStatusComponent()->SetGold(player->GetStatusComponent()->GetGold() - sellItem.price);
					sellItem.count--;
					OnChangeSaveItemCount.Broadcast(sellItem.count);
					OnChangeSaveItemCount.Clear();
				}
			}
			break;
		}
	}
}

void ANPCBase::SellItem(APlayerCharacter* player, const FName& itemCode)
{
	auto invenComp = player->GetinventoryComponent();
	if (invenComp != nullptr)
	{
		auto info = invenComp->GetItemInfo(itemCode);
		if (info != nullptr)
		{
			const auto price = info->sellPrice;
			//DecreaseItemCount 를 bool형으로 반환해서 성공적으로 아이템을 비웠을경우 골드를 받는거로 변경하자!
			auto bSell = invenComp->DecreaseItemCount(itemCode);
			if (bSell)
			{
				player->GetStatusComponent()->SetGold(player->GetStatusComponent()->GetGold() + price);

				auto storedItem = invenComp->GetItem(itemCode);
				if (storedItem != nullptr)
				{
					OnChangeSellItemCount.Broadcast(storedItem->item_Count);
				}
				else
				{
					OnChangeSellItemCount.Broadcast(0);
				}
			}
				OnChangeSellItemCount.Clear();
		}
	}
}

