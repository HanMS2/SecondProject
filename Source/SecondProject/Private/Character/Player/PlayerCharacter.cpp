// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Character/Equipment/EquipmentActor.h"
#include "Character/Component/StatusComponent.h"
#include "Character/Component/LockOnComponent.h"
#include "Widget/ShowDamageWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Character/Player/Controller/CustomController.h"
#include "Character/Player/Component/InventoryComponent.h"
#include "Item/ItemActor.h"


APlayerCharacter::APlayerCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = originalRotationRate; // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	lockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("lockOnComp"));
	inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("inventoryComp"));
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	Helmet =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Helmet"));
	Helmet->SetupAttachment(GetMesh());
	Chest  =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest"));
	Chest->SetupAttachment(GetMesh());
	Glove  =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Glove"));
	Glove->SetupAttachment(GetMesh());
	Leg    =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Leg"));
	Leg->SetupAttachment(GetMesh());
	Boot   =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Boot"));
	Boot->SetupAttachment(GetMesh());

	SetGenericTeamId(FGenericTeamId(0));

}

//Value : -1 ~ 1
void APlayerCharacter::MoveForward(float Value)
{
	if (bRun) {
		moveForward = Value * 2;
	}
	else {
		moveForward = Value;
	}

	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{

	if (bRun) {
		moveRight = Value * 2;
	}
	else {
		moveRight = Value;
	}

	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{	
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::AddControllerYawInput(float Val)
{
	if (bLockOn == false) {
		Super::AddControllerYawInput(Val);
	}
	else {
		//-10(왼쪽) ~ 10(오른쪽)
		//만약 마우스를 오른쪽으로 움직였을 경우
		if (Val >= 2.f) {
			//락온컴포넌트의 NextLockOnTarget호출
			if (GetWorldTimerManager().TimerExists(nextLockOnTargetTimerHandle) == false) {
				GetWorldTimerManager().SetTimer(nextLockOnTargetTimerHandle, lockOnComponent, &ULockOnComponent::PreLockOnTarget, 0.2f);
			}
			
		}
		//마우스를 왼쪽으로 움직였을 경우.
		else if (Val <= -2.f) {
			//락온컴포넌트의 PreLockOnTarget호출
			if (GetWorldTimerManager().TimerExists(nextLockOnTargetTimerHandle) == false) {
				GetWorldTimerManager().SetTimer(nextLockOnTargetTimerHandle, lockOnComponent, &ULockOnComponent::NextLockOnTarget, 0.2f);
			}
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);


	PlayerInputComponent->BindAction("EquipWeapon", IE_Pressed, this, &APlayerCharacter::EquipWeapon);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &APlayerCharacter::StopAttack);


	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::StopRun);


	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &APlayerCharacter::Roll);

	PlayerInputComponent->BindAction("Guard", IE_Pressed, this, &APlayerCharacter::Guard);
	PlayerInputComponent->BindAction("Guard", IE_Released, this, &APlayerCharacter::Guard);

	PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &APlayerCharacter::LockOn);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::OpenInventory);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &APlayerCharacter::PickUp);

	//퀵슬롯 바인딩
	PlayerInputComponent->BindAction("QuickUp", IE_Pressed, this, &APlayerCharacter::QuickUp);
	
	PlayerInputComponent->BindAction("QuickDown", IE_Pressed, this, &APlayerCharacter::QuickDown);

	PlayerInputComponent->BindAction("UseQuick", IE_Pressed, this, &APlayerCharacter::UseQuick);
	
	//마우스 커서보기.

}

void APlayerCharacter::SpawnEquipment()
{
	if (equipmentClass != nullptr)
	{
		spawndWeapon = GetWorld()->SpawnActor<AEquipmentActor>(equipmentClass.Get());

		if (spawndWeapon != nullptr)
		{
			spawndWeapon->SetOwner(this);
		}
		spawndShield = GetWorld()->SpawnActor<AEquipmentActor>(equipmentClass.Get());

		if (spawndShield != nullptr)
		{
			spawndShield->SetOwner(this);
		}
	}
}

void APlayerCharacter::EquipWeapon()
{
	auto equipInfo = inventoryComponent->GetEquippedItem();
	if (equipInfo.GetWeapon() == nullptr)
	{
		return;
	}

	if (bReadyCombat == true) {
		if (equipInfo.GetWeapon()->UnEquipMontage != nullptr && GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == false) {
			GetMesh()->GetAnimInstance()->Montage_Play(equipInfo.GetWeapon()->UnEquipMontage);
			bReadyCombat = false;
		}
	}
}



/*
	공격키 눌렀을떄 무기 집어넣은 상태면, 꺼내게 해 주십쇼.
*/
void APlayerCharacter::Attack()
{	
		if (spawndWeapon != nullptr)
		{
			spawndWeapon->Attack();
		}
		else 
		{
			UE_LOG(LogTemp, Error, TEXT("APlayerCharacter::Attack() - weapon is null"));
		}
}

void APlayerCharacter::StopAttack()
{
	bAttack = false;
}

void APlayerCharacter::Run()
{
	//아무 방향키 입력이 없으면, 아무것도 안함.
	if (moveForward == 0 && moveRight == 0) {
		return;
	}

	bRun = true;
	GetStatusComponent()->PauseRecoverStaminaPerTime();
	GetCharacterMovement()->MaxWalkSpeed = 900;

	if (GetWorldTimerManager().IsTimerActive(RunStaminaTimerHandle) == false)
	{
		FTimerDelegate runTimerDelegate = FTimerDelegate::CreateUObject
		(GetStatusComponent(),&UStatusComponent::RemoveStamina,7.f);
		GetWorldTimerManager().SetTimer(RunStaminaTimerHandle, runTimerDelegate, 1.f, true);
	}
}

void APlayerCharacter::StopRun()
{
	bRun = false;
	GetStatusComponent()->ResumeRecoverStaminaPerTime();
	GetCharacterMovement()->MaxWalkSpeed = 600;

	if (GetWorldTimerManager().IsTimerActive(RunStaminaTimerHandle) == true)
	{
		GetWorldTimerManager().ClearTimer(RunStaminaTimerHandle);
	}

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetStatusComponent()->RecoverStaminaPerTime(1.0f);


}

void APlayerCharacter::Roll()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == false) 
	{

		if (spawndWeapon != nullptr)
		{
			spawndWeapon->Roll();

		}
	}
}

void APlayerCharacter::Guard()
{

	auto equipInfo = inventoryComponent->GetEquippedItem();
	if (equipInfo.GetWeapon() == nullptr)
	{
		return;
	}

	if (spawndWeapon != nullptr)
	{
		spawndWeapon->Guard();
	}
	
}

bool APlayerCharacter::GuardProcess(FVector hitLocation)
{
	auto equipInfo = inventoryComponent->GetEquippedItem();
	if (equipInfo.GetWeapon() == nullptr)
	{
		return false;
	}



	if (spawndWeapon != nullptr)
	{
		return spawndWeapon->GuardProcess(hitLocation);
	}

	return false;
}

void APlayerCharacter::HitProcess(FVector hitLocation)
{
	auto equipInfo = inventoryComponent->GetEquippedItem();
	if (equipInfo.GetWeapon() == nullptr)
	{
		return;
	}
	if (spawndWeapon != nullptr)
	{
		spawndWeapon->HitProcess(hitLocation);
	}
	
	/*
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
		GetMesh()->GetAnimInstance()->Montage_Play(gotHit_CenterMontage);
	}
	else if (-135 <= yaw && yaw < -45) {
		UE_LOG(LogTemp, Log, TEXT("left"));
		GetMesh()->GetAnimInstance()->Montage_Play(gotHit_LeftMontage);
	}
	else if (45 < yaw && yaw <= 135) {
		UE_LOG(LogTemp, Log, TEXT("right"));
		GetMesh()->GetAnimInstance()->Montage_Play(gotHit_RightMontage);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("back"));
		GetMesh()->GetAnimInstance()->Montage_Play(gotHit_BackMontage);
	}

	if (gotHitParticle != nullptr) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), gotHitParticle, hitLocation);
	}
	*/
}

void APlayerCharacter::LockOn()
{

	if (bReadyCombat == true) {
		bLockOn = !bLockOn;

		if (bLockOn) {
			lockOnComponent->SetLockOn();
		}
		else {
			lockOnComponent->StopLockOn();
		}
	}
}

void APlayerCharacter::QuickUp()
{
	inventoryComponent->QuickUp();
}

void APlayerCharacter::QuickDown()
{
	inventoryComponent->QuickDown();
}

void APlayerCharacter::UseQuick()
{
	inventoryComponent->UseQuick();
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	FHitResult hit;
	FVector vec;
	DamageEvent.GetBestHitInfo(this, DamageCauser, hit, vec);

	if (bGuard) {

		
			if (statusComponent->CheckStamina(30)) {

				if (GuardProcess(hit.ImpactPoint)) 
				{
					statusComponent->SetSP(statusComponent->GetSP() - 30);
					DamageAmount = 0;
				}
			}
		
	}
	else {
		HitProcess(hit.ImpactPoint);
	}

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	return 0.0f;
}

void APlayerCharacter::ShowDamage(float damage, FVector hitLocation)
{
	UE_LOG(LogTemp, Log, TEXT("ShowDamage : %s"), *hitLocation.ToString());

	auto comp = NewObject<UWidgetComponent>(this, damageWidgetComponentClass.Get());
	if (comp != nullptr) {
		comp->RegisterComponent();

		auto damageWidget = Cast<UShowDamageWidget>(comp->GetUserWidgetObject());
		if (damageWidget != nullptr) {
			damageWidget->SetDamageText(damage);
		}
		FVector randLocation = FVector(FMath::RandRange(0, 50), FMath::RandRange(0, 50), FMath::RandRange(0, 50));
		comp->SetWorldLocation(hitLocation + randLocation);
	}
}

void APlayerCharacter::OpenInventory()
{
	auto con = Cast<ACustomController>(GetController());
	if (con != nullptr) {
		con->ShowInventory();
	}
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddUniqueDynamic(this, &APlayerCharacter::OnBeginOverlapEvent);
	OnActorEndOverlap.AddUniqueDynamic(this, &APlayerCharacter::OnEndOverlapEvent);
}

void APlayerCharacter::OnBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<AItemActor>()) {
		pickUPItem = Cast<AItemActor>(OtherActor);

		pickUPItem->GetWidgetComponent()->SetVisibility(true);
	}
}

void APlayerCharacter::OnEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == pickUPItem)
	{
		pickUPItem->GetWidgetComponent()->SetVisibility(false);
		pickUPItem = nullptr;
	}
}

void APlayerCharacter::PickUp()
{
	if (pickUPItem != nullptr)
	{
		inventoryComponent->AddItem(pickUPItem);
		pickUPItem->Destroy();
		pickUPItem = nullptr;
	}
}

UInventoryComponent* APlayerCharacter::GetinventoryComponent()
{
	return inventoryComponent;
}

void APlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	Helmet->SetMasterPoseComponent(GetMesh());
	Glove->SetMasterPoseComponent(GetMesh());
	Chest->SetMasterPoseComponent(GetMesh());
	Leg->SetMasterPoseComponent(GetMesh());
	Boot->SetMasterPoseComponent(GetMesh());

}
