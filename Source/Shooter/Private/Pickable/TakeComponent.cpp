// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable/TakeComponent.h"


#include "GameFramework/Character.h"


UTakeComponent::UTakeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	
}

void UTakeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

bool UTakeComponent::TryTakeItem(ABasePickableItem* Item)
{
	if(TakenItems.Num() > 3)
		return false;
	
	CurrentTakenItem = TakenItems.Add(Item);
	
	const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
	                                            EAttachmentRule::KeepRelative, true);
	Item->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), AttachRules);
	
	return true;
}

bool UTakeComponent::TryUseCurrentItem()
{
	if(!CanUseCurrentItem())
		return false;
	
	IUseInterface::Execute_Use(TakenItems[CurrentTakenItem]);
	
	return true;
}

bool UTakeComponent::CanUseCurrentItem()
{
	if(CurrentTakenItem == -1)
		return false;

	UObject* UseObject = TakenItems[CurrentTakenItem];
	
	if(!UseObject->Implements<UUseInterface>())
		return false;

	if(!IUseInterface::Execute_CanUse(UseObject))
		return false;

	return true;
}
