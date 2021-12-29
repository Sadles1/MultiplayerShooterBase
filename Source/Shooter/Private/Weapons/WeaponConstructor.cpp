// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponConstructor.h"
#include "Weapons/BaseWeapon.h"

ABaseWeapon* UWeaponConstructor::SpawnWeapon(const UObject* WorldContextObject,
                                             const TSubclassOf<ABaseWeapon> WeaponClass,
                                             const FVector_NetQuantize& SpawnLocation)
{
	const FTransform SpawnTransform(SpawnLocation);
	return WorldContextObject->GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass, SpawnTransform);
}
