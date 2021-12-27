// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AutoRifleWeapon.h"

void AAutoRifleWeapon::StartFire()
{
	Super::StartFire();

	GetWorldTimerManager().SetTimer(AutoFireTimer, this, &AAutoRifleWeapon::TryShoot, GetFireRate(), true, 0.f);
}

void AAutoRifleWeapon::StopFire()
{
	Super::StopFire();

	GetWorldTimerManager().ClearTimer(AutoFireTimer);
	AutoFireTimer.Invalidate();
}

