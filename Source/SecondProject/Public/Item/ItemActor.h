// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "Item/ItemTypes.h"

#include "ItemActor.generated.h" // 헤더에 헤더를 추가할경우 반드시 <<이헤더가 아래에 있어야한다.


UCLASS()
class SECONDPROJECT_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* sphereComponent;
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* particleComponent;


	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* widgetComponent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int32 item_Count = 1;

	UPROPERTY(EditAnywhere)
		FName item_Code;

	UPROPERTY(EditAnywhere)
		class UDataTable* itemTable;


public:


	void SetItemCount(const int32& newCount) { item_Count = newCount; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UWidgetComponent* GetWidgetComponent() { return widgetComponent; }
	FName GetItemCode() { return item_Code; }
	void SetItemCode(const FName& newCode) { item_Code = newCode; }
	virtual void UseItem(AActor* target) {}

	virtual void UnEquip(AActor* target, const FEquipmentInformation* info) {}


	const int32& GetItemCount() {return item_Count;}

	template<typename T>
	T* GetItemInformation();

};

template<typename T>
inline T* AItemActor::GetItemInformation()
{
	if (itemTable != nullptr)
	{
		return itemTable->FindRow<T>(item_Code, "");
	}
	return nullptr;
}
