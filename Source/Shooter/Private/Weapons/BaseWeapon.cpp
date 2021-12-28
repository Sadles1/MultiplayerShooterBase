// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"


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
	check(HasAuthority())
	CurrentState = EWeaponState::WS_Fire;
}
void ABaseWeapon::StopFire()
{
	check(HasAuthority())
	CurrentState = EWeaponState::WS_None;
}

void ABaseWeapon::StartReload()
{
	if(CurrentState == EWeaponState::WS_Fire)
		StopFire();

	CurrentState = EWeaponState::WS_Reload;
	GetWorldTimerManager().SetTimer(ReloadTimer, this, &ABaseWeapon::Reload, ReloadTime, false);
}
void ABaseWeapon::Reload()
{
	Ammo = AmmoInClip;
	EndReload();
}

void ABaseWeapon::EndReload()
{
	CurrentState = EWeaponState::WS_None;
	GetWorldTimerManager().ClearTimer(ReloadTimer);
}

bool ABaseWeapon::CanReload()
{
	if(Ammo >= AmmoInClip)
		return false;
	
	if(CurrentState == EWeaponState::WS_Reload)
		return false;
	
	return true;
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

float ABaseWeapon::GetFireRate() const
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
}

FText ABaseWeapon::GetWeaponName() const
{
	return Name;
}

bool ABaseWeapon::TryReload()
{
	check(HasAuthority())
	if(CanReload())
	{
		StartReload();
		return true;
	}

	return false;
}

float ABaseWeapon::GetCurrentAmmo() const
{
	return Ammo;
}
float ABaseWeapon::GetAmmoInClip() const
{
	return AmmoInClip;
}

bool ABaseWeapon::CanInteract_Implementation(AController* Controller)
{
	return true;
}

void ABaseWeapon::Interact_Implementation(AController* Controller)
{
	PickupComponent->TryPickItem(Controller);
}

void ABaseWeapon::OnRep_Ammo() const
{
	AmmoChanged.Broadcast(Ammo);
}

void ABaseWeapon::OnRep_CurrentState() const
{
	StateChanged.Broadcast(CurrentState);
}

void ABaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ABaseWeapon, Ammo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ABaseWeapon, AmmoInClip, COND_OwnerOnly);
	DOREPLIFETIME(ABaseWeapon, CurrentState);
}
