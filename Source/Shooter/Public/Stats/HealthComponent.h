// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeath);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UHealthComponent();
	
	FDeath Death;

	virtual void TakeDamage(float Damage);
protected:
	
	virtual void BeginPlay() override;

	
	
	bool IsDead() const;

	void OnOwnerDeath();

private:

	UPROPERTY(VisibleInstanceOnly, Category = "Health")
	float CurrentHealth = 100.f;
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.f;

	bool Dead = false;
	
};
