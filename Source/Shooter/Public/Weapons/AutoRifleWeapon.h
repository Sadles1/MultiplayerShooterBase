// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"


#include "BaseWeapon.h"


#include "AutoRifleWeapon.generated.h"


UCLASS()
class SHOOTER_API AAutoRifleWeapon : public ABaseWeapon
{
	
	GENERATED_BODY()

	
public:

	
protected:

	virtual void StartFire() override;
	virtual void StopFire() override;

	
private:

	FTimerHandle AutoFireTimer;
};
