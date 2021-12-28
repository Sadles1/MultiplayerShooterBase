// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickable/TakeInterface.h"
#include "Weapons/BaseWeapon.h"
#include "BasePlayerController.generated.h"

UCLASS()
class SHOOTER_API ABasePlayerController : public APlayerController, public ITakeInterface
{
	GENERATED_BODY()

public:
	
	ABasePlayerController();

	
protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual UTakeComponent* GetTakeComponent() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SpawnWeapon(TSubclassOf<ABaseWeapon> WeaponClass);

	
private:

	UFUNCTION(BlueprintCallable)
	void TraceForwardDirection(float Distance, FHitResult& HitResult) const;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_Interact();

	

	bool TryInteract();
	
};
