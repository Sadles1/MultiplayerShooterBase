// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Interact/InteractInterface.h"
#include "Pickable/PickupComponent.h"
#include "Pickable/UseInterface.h"


#include "BaseWeapon.generated.h"


UENUM()
enum class EWeaponState : uint8
{
	WS_None UMETA(DisplayName = "None"),
	WS_Reload UMETA(DisplayName = "Reload"),
	WS_Fire UMETA(DisplayName = "Fire"),

	WS_MAX
};


UCLASS(Abstract)
class SHOOTER_API ABaseWeapon : public AActor, public IUseInterface, public IInteractInterface
{
	GENERATED_BODY()

public:
	
	ABaseWeapon();

	
protected:
	
	virtual void BeginPlay() override;

	virtual void StartFire();
	virtual void StopFire();

	void TryShoot();

	float GetFireRate();

private:

	virtual void MakeShoot();

	virtual bool CanInteract_Implementation(AController* Controller) override;
	virtual void Interact_Implementation(AController* Controller) override;

	virtual bool CanUse_Implementation() override;
	virtual void StartUse_Implementation() override;
	virtual void StopUse_Implementation() override;

	virtual bool CanStartFire();

	UPROPERTY(EditAnywhere, Category = "Stats")
	float FireRange = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float Damage = 20.f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float FireSpeed = 200.f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	uint32 Ammo = 15;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
	UPickupComponent* PickupComponent = nullptr;

	UPROPERTY()
	EWeaponState CurrentState;
};
