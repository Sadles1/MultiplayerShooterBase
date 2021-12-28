// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponConstructor.generated.h"


class ABaseWeapon;
UCLASS()
class SHOOTER_API UWeaponConstructor : public UObject
{
	
	GENERATED_BODY()
	
public:

	static ABaseWeapon* SpawnWeapon(const UObject* WorldContextObject, const TSubclassOf<ABaseWeapon> WeaponClass, const FVector_NetQuantize& SpawnLocation);
	
};
