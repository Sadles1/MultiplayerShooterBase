// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"


#include "BaseWeapon.h"


#include "PistolWeapon.generated.h"


UCLASS()
class SHOOTER_API APistolWeapon : public ABaseWeapon
{
	GENERATED_BODY()

	
public:
	
	APistolWeapon();
	
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void StartFire() override;
	virtual void StopFire() override;

	FTimerHandle FireTimer;

};
