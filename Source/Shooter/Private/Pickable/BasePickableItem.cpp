// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable/BasePickableItem.h"

#include "Pickable/TakeInterface.h"


ABasePickableItem::ABasePickableItem()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
}

void ABasePickableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABasePickableItem::CanInteract_Implementation(AController* Controller)
{
	return true;
}

void ABasePickableItem::Interact_Implementation(AController* Controller)
{
	if(!Controller->Implements<UTakeInterface>())
		return;
	
	UTakeComponent* TakeComponent =	Cast<ITakeInterface>(Controller)->GetTakeComponent();
	TakeComponent->TryTakeItem(this);
}

void ABasePickableItem::Use_Implementation() {}

bool ABasePickableItem::CanUse_Implementation()
{
	return true;
}
