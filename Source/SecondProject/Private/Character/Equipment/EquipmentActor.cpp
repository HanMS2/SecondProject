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

			//라인트레이스가 검출할 오브젝트 타입을 설정합니다.
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));

			//라인트레이스에서 무엇인가 검출하면, 이 배열에 저장됩니다.
			TArray<FHitResult> hits;

			//라인트레이스를 그립니다. Multi형태기 때문에 선 중간에 무엇인가 있더라도 멈추지 않고 그립니다.
			if (UKismetSystemLibrary::LineTraceMultiForObjects(this,
				//트레이스 시작 지점.
				GetActorLocation(),
				//트레이스 끝 지점.
				OtherActor->GetActorLocation(),
				//트레이스가 감지해야 할 오브젝트 타입이 들어잇는 배열
				ObjectTypes,
				//복잡한 콜리전검사를 할 것인가?
				false,
				//이 트레이스가 무시해야 할 대상
				TArray<AActor*>(),
				//트레이스 디버그 타입
				EDrawDebugTrace::ForOneFrame,
				//트레이스가 검출할 정보를 저장할 Hit 구조체 배열
				hits,
				//자기자신을 무시할 것인가?
				true)) {

				for (auto i = 0; i < hits.Num(); i++) {
					if (hits[i].GetActor() == OtherActor) {
						if (hitParticle != nullptr) {
							//파티클을 스폰합니다.
							UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, hits[i].Location);
						}

						if (hitSound != nullptr) {
							//사운드를 재생합니다.
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


	//1.hitLocation 과 플레이어 사이의 각도.
	FRotator rot = (hitLocation - GetActorLocation()).Rotation();
	//1번 각도랑, 현재 플레이어의 로테이션을 이용하면, 좌 우 를 알수 있음.
	float yaw = (rot - GetActorRotation()).Yaw;

	//알아보기 쉽게 한번 가공함.
	if (yaw > 180) {
		yaw -= 360;
	}
	else if (yaw < -180) {
		yaw += 360;
	}


	//앞 -45 ~ 45 = 90
	//좌 (-90-45) ~ -45 = 90
	//우 45 ~ (90+45) = 90
	//후 나머지

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

