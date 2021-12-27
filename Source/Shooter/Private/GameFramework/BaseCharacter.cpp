// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework\BaseCharacter.h"

#include "Stats/HealthComponent.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	TakeComponent = CreateDefaultSubobject<UTakeComponent>(TEXT("TakeComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealtComponent"));
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	if(HasAuthority())
		HealthComponent->Death.AddDynamic(this, &ABaseCharacter::OnDeath);
}

UTakeComponent* ABaseCharacter::GetTakeComponent()
{
	return TakeComponent;
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	HealthComponent->TakeDamage(DamageAmount);

	return DamageAmount;
}

void ABaseCharacter::OnDeath_Implementation()
{
	
}
