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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAmmoChanged, float, NewAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateChange, EWeaponState, NewState);


UCLASS(Abstract)
class SHOOTER_API ABaseWeapon : public AActor, public IUseInterface, public IInteractInterface
{
	GENERATED_BODY()

public:
	
	ABaseWeapon();

	UFUNCTION(BlueprintCallable)
	FText GetWeaponName() const;
	
	virtual bool TryReload();

	UFUNCTION(BlueprintCallable)
	float GetCurrentAmmo() const;
	UFUNCTION(BlueprintCallable)
	float GetAmmoInClip() const;

	
public:
	
	UPROPERTY(BlueprintAssignable)
	FAmmoChanged AmmoChanged;
	UPROPERTY(BlueprintAssignable)
	FStateChange StateChanged;
	
protected:
	
	virtual void BeginPlay() override;

	virtual void StartFire();
	virtual void StopFire();
	
	virtual bool CanReload();

	void TryShoot();
	float GetFireRate() const;

private:

	virtual bool CanInteract_Implementation(AController* Controller) override;
	virtual void Interact_Implementation(AController* Controller) override;

	virtual bool CanUse_Implementation() override;
	virtual void StartUse_Implementation() override;
	virtual void StopUse_Implementation() override;

	
	virtual void MakeShoot();
	virtual bool CanStartFire();
	
	void StartReload();
	virtual void Reload();
	void EndReload();


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_Ammo() const;
	UFUNCTION()
	void OnRep_CurrentState() const;
	
private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Info")
	FText Name = FText::FromString("Weapon");

	UPROPERTY(EditAnywhere, Category = "Stats")
	float FireRange = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float Damage = 20.f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float FireSpeed = 200.f;

	
	
	UPROPERTY(ReplicatedUsing = OnRep_Ammo, VisibleInstanceOnly, Category = "Stats")
	uint32 Ammo = 15;
	UPROPERTY(Replicated, EditAnywhere, Category = "Stats")
	uint32 AmmoInClip = 15;

	UPROPERTY(EditAnywhere, Category = "Stats|Reloading")
	float ReloadTime = 1.f;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
	UPickupComponent* PickupComponent = nullptr;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentState, VisibleInstanceOnly, Category = "Info")
	EWeaponState CurrentState;

	FTimerHandle ReloadTimer;
};
