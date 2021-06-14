// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Equipment/EquipmentActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Monster/Monster.h"
#include "Character/Player/PlayerCharacter.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "..\..\..\Public\Character\Equipment\EquipmentActor.h"
#include "Character/Component/StatusComponent.h"
#include "Character/Player/Component/InventoryComponent.h"

// Sets default values
AEquipmentActor::AEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("skeletalMesh"));
	RootComponent = skeletalMesh;

	skeletalMesh->SetCollisionProfileName("Weapon");
	skeletalMesh->SetGenerateOverlapEvents(true);
	skeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

// Called when the game starts or when spawned
void AEquipmentActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEquipmentActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddUniqueDynamic(this, &AEquipmentActor::OnBeginOverlapEvent);
}

void AEquipmentActor::OnBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<AMonster>() == true) {

		if (hitActors.Contains(OtherActor) == false) {
			UE_LOG(LogTemp, Log, TEXT("%s"), *OtherActor->GetName());

			OtherActor->TakeDamage(10.f, FDamageEvent(), nullptr, this);
			hitActors.AddUnique(OtherActor);

			//����Ʈ���̽��� ������ ������Ʈ Ÿ���� �����մϴ�.
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));

			//����Ʈ���̽����� �����ΰ� �����ϸ�, �� �迭�� ����˴ϴ�.
			TArray<FHitResult> hits;

			//����Ʈ���̽��� �׸��ϴ�. Multi���±� ������ �� �߰��� �����ΰ� �ִ��� ������ �ʰ� �׸��ϴ�.
			if (UKismetSystemLibrary::LineTraceMultiForObjects(this,
				//Ʈ���̽� ���� ����.
				GetActorLocation(),
				//Ʈ���̽� �� ����.
				OtherActor->GetActorLocation(),
				//Ʈ���̽��� �����ؾ� �� ������Ʈ Ÿ���� ����մ� �迭
				ObjectTypes,
				//������ �ݸ����˻縦 �� ���ΰ�?
				false,
				//�� Ʈ���̽��� �����ؾ� �� ���
				TArray<AActor*>(),
				//Ʈ���̽� ����� Ÿ��
				EDrawDebugTrace::ForOneFrame,
				//Ʈ���̽��� ������ ������ ������ Hit ����ü �迭
				hits,
				//�ڱ��ڽ��� ������ ���ΰ�?
				true)) {

				for (auto i = 0; i < hits.Num(); i++) {
					if (hits[i].GetActor() == OtherActor) {
						if (hitParticle != nullptr) {
							//��ƼŬ�� �����մϴ�.
							UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, hits[i].Location);
						}

						if (hitSound != nullptr) {
							//���带 ����մϴ�.
							UGameplayStatics::SpawnSoundAtLocation(this, hitSound, hits[i].Location);
						}


						auto player = Cast<APlayerCharacter>(GetOwner());
						if (player != nullptr) {
							player->ShowDamage(10.f, hits[i].Location);
						}

					}
				}
			}
		}

	}
}

void AEquipmentActor::AddHitActor(AActor* hitActor)
{
	hitActors.AddUnique(hitActor);
}

void AEquipmentActor::ClearHitActors()
{
	hitActors.Empty();
}

// Called every frame
void AEquipmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquipmentActor::HitProcess(const FVector& hitLocation)
{
	auto mesh = Cast<APlayerCharacter>(GetOwner())->GetMesh();
	auto equipInfo = GetInventoryComponent()->GetEquippedItem();

	if (mesh == nullptr || equipInfo.GetWeapon() == nullptr)
	{
		return;
	}


	//1.hitLocation �� �÷��̾� ������ ����.
	FRotator rot = (hitLocation - GetActorLocation()).Rotation();
	//1�� ������, ���� �÷��̾��� �����̼��� �̿��ϸ�, �� �� �� �˼� ����.
	float yaw = (rot - GetActorRotation()).Yaw;

	//�˾ƺ��� ���� �ѹ� ������.
	if (yaw > 180) {
		yaw -= 360;
	}
	else if (yaw < -180) {
		yaw += 360;
	}


	//�� -45 ~ 45 = 90
	//�� (-90-45) ~ -45 = 90
	//�� 45 ~ (90+45) = 90
	//�� ������

	UE_LOG(LogTemp, Log, TEXT("%f"), yaw);

	if (-45 <= yaw && yaw <= 45) {
		UE_LOG(LogTemp, Log, TEXT("front"));
		mesh->GetAnimInstance()->Montage_Play(equipInfo.GetWeapon()->gotHit_CenterMontage);
	}
	else if (-135 <= yaw && yaw < -45) {
		UE_LOG(LogTemp, Log, TEXT("left"));
		mesh->GetAnimInstance()->Montage_Play(equipInfo.GetWeapon()->gotHit_LeftMontage);
	}
	else if (45 < yaw && yaw <= 135) {
		UE_LOG(LogTemp, Log, TEXT("right"));
		mesh->GetAnimInstance()->Montage_Play(equipInfo.GetWeapon()->gotHit_RightMontage);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("back"));
		mesh->GetAnimInstance()->Montage_Play(equipInfo.GetWeapon()->gotHit_BackMontage);
	}

	if (equipInfo.GetWeapon()->gotHitParticle != nullptr) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), equipInfo.GetWeapon()->gotHitParticle, hitLocation);
	}
}

UInventoryComponent* AEquipmentActor::GetInventoryComponent()
{
	auto player = Cast<APlayerCharacter>(GetOwner());
	if (player != nullptr)
	{
		return player->GetinventoryComponent();
	}

	return nullptr;
}

UStatusComponent* AEquipmentActor::GetStatusComponent()
{
	auto player = Cast<APlayerCharacter>(GetOwner());
	if (player != nullptr)
	{
		return	player->GetStatusComponent();
	}
	return nullptr;
}

float AEquipmentActor::PlayMontage(UAnimMontage* montage)
{
	auto player = Cast<APlayerCharacter>(GetOwner());
	if (player != nullptr)
	{
		return player->GetMesh()->GetAnimInstance()->Montage_Play(montage);
	
	}
	return 0;
}

bool AEquipmentActor::isPlayingAnyMontage()
{
	auto player = Cast<APlayerCharacter>(GetOwner());
	if (player != nullptr)
	{
		return player->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying();

	}

	return true;
}

