// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/PistolWeapon.h"

APistolWeapon::APistolWeapon()
{
	
}

void APistolWeapon::StartFire()
{
	Super::StartFire();

	GetWorldTimerManager().SetTimer(FireTimer, this, &APistolWeapon::StopFire, GetFireRate(), false);
	TryShoot();
}

void APistolWeapon::StopFire()
{
	Super::StopFire();

	GetWorldTimerManager().ClearTimer(FireTimer);
	FireTimer.Invalidate();
}

void APistolWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

