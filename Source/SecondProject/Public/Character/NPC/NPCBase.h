// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "NPCBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeSaveItemCount, const int32&, changedCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeSellItemCount, const int32&, changedCount);

USTRUCT(BlueprintType)
struct FNPCSellItem : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor>	sellItemClass;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "!bInfinite"))
		int32 count;
	UPROPERTY(EditAnywhere)
		int32 price;
	UPROPERTY(EditAnywhere)
		bool bInfinite = false;
};


UCLASS()
class SECONDPROJECT_API ANPCBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCBase();


protected:
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
		class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
		class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		TArray<FName> chat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		FName npcName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		class UDataTable* sellTable;
	
	TArray<FNPCSellItem> sellItemList;
	const TArray<FNPCSellItem*> GetSellItemList();

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UNPCDialogWidget> dialogWidgetClass;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Interaction(APlayerController* controller);

	const FName& GetNPCName() { return npcName; }
	TArray<FName> GetChat() { return chat; }
	//플레이어가 아이템을 산다.
	void BuyItem(class APlayerCharacter* player, const FName& itemCode);
	
	//플레이어가 아이템을 판다
	void SellItem(class APlayerCharacter* player, const FName& itemCode);

	const TArray<FNPCSellItem>& GetSavedSellItemList() { return sellItemList; }

	FOnChangeSaveItemCount OnChangeSaveItemCount;
	FOnChangeSellItemCount OnChangeSellItemCount;
};
