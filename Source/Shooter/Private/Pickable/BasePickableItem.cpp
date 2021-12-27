// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable/BasePickableItem.h"


ABasePickableItem::ABasePickableItem()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComponent"));
}

void ABasePickableItem::BeginPlay()
{
	Super::BeginPlay();

	check(PickupComponent);
}

bool ABasePickableItem::CanInteract_Implementation(AController* Controller)
{
	return true;
}

void ABasePickableItem::Interact_Implementation(AController* Controller)
{
	PickupComponent->TryPickItem(Controller);
}
