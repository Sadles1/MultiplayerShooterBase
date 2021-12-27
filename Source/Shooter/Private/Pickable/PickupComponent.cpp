// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable/PickupComponent.h"
#include "Pickable/TakeInterface.h"


UPickupComponent::UPickupComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

bool UPickupComponent::TryPickItem(AController* Controller)
{
	if(!Controller->Implements<UTakeInterface>())
		return false;
	
	UTakeComponent* TakeComponent =	Cast<ITakeInterface>(Controller)->GetTakeComponent();
	check(TakeComponent);
	TakeComponent->TryTakeItem(GetOwner());
	return true;
}
