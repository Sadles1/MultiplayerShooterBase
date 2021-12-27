// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


ABaseWeapon::ABaseWeapon()
{
	bReplicates = true;


	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SetRootComponent(Mesh);
	
	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComponent"));
	
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(PickupComponent);
}

bool ABaseWeapon::CanUse_Implementation()
{
	return true;
}

void ABaseWeapon::StartUse_Implementation()
{
	if(CanStartFire())
		StartFire();
}

void ABaseWeapon::StopUse_Implementation()
{
	if(CurrentState == EWeaponState::WS_Fire)
		StopFire();
}

bool ABaseWeapon::CanStartFire()
{
	return CurrentState != EWeaponState::WS_Reload && CurrentState != EWeaponState::WS_Fire;
}

void ABaseWeapon::StartFire()
{
	CurrentState = EWeaponState::WS_Fire;
}
void ABaseWeapon::StopFire()
{
	CurrentState = EWeaponState::WS_None;
}

void ABaseWeapon::TryShoot()
{
	if(Ammo > 0)
	{
		MakeShoot();

		Ammo--;
	}
	else
		StopFire();
}

float ABaseWeapon::GetFireRate()
{
	return 60.f / FireSpeed;
}

void ABaseWeapon::MakeShoot()
{
	AController* Controller = Cast<APawn>(GetOwner())->GetController();

	FVector ActorLocation;
	const FRotator ActorRotation = Controller->GetControlRotation();
	
	if(Cast<APlayerController>(Controller))
		ActorLocation = Cast<APlayerController>(Controller)->PlayerCameraManager->GetCameraLocation();
	else
		ActorLocation = Controller->GetPawn()->GetActorLocation();

	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ActorRotation);

	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		ActorLocation,
		ActorLocation + ForwardVector * FireRange,
		TraceTypeQuery3,
		false,
		{GetOwner()},
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
	);

	if(!HitResult.bBlockingHit)
		return;

	if(HitResult.GetActor())
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, Controller, GetOwner(), UDamageType::StaticClass());

	//HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), Controller, this);
}

bool ABaseWeapon::CanInteract_Implementation(AController* Controller)
{
	return true;
}

void ABaseWeapon::Interact_Implementation(AController* Controller)
{
	PickupComponent->TryPickItem(Controller);
}
