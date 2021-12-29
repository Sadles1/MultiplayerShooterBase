// Fill out your copyright notice in the Description page of Project Settings.


#include "Stats/HealthComponent.h"


#include "Net/UnrealNetwork.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//I don't know why this dont work
	//if(GetOwnerRole() == ROLE_Authority)
		//GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	
}

void UHealthComponent::TakeDamage(float Damage)
{
	if(IsDead())
		return;
	
	CurrentHealth -= Damage;

	if(CurrentHealth <= 0.f)
		OnOwnerDeath();
}

bool UHealthComponent::IsDead() const
{
	return Dead;
}

void UHealthComponent::OnOwnerDeath()
{
	Dead = true;
	Death.Broadcast();
}

void UHealthComponent::OnRep_Dead() const
{
	Death.Broadcast();
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Dead);
}
