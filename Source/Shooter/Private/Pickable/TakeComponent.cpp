// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable/TakeComponent.h"
#include "GameFramework/Character.h"
#include "Pickable/UseInterface.h"


UTakeComponent::UTakeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	
}

void UTakeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}




bool UTakeComponent::TryTakeItem(AActor* Item)
{
	if(TakenItems.Num() > 3)
		return false;
	
	CurrentTakenItem = TakenItems.Add(Item);
	
	const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
	                                            EAttachmentRule::KeepRelative, true);
	Cast<AActor>(Item)->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), AttachRules);
	
	return true;
}

void UTakeComponent::StartUseCurrentItem()
{
	if(!CanUseCurrentItem())
		return;
	
	IUseInterface::Execute_StartUse(TakenItems[CurrentTakenItem]);
}

void UTakeComponent::StopUseCurrentItem()
{
	if(!IsCurrentItemValidForUse())
		return;

	IUseInterface::Execute_StopUse(TakenItems[CurrentTakenItem]);
}

bool UTakeComponent::CanUseCurrentItem()
{
	return IsCurrentItemValidForUse() && CanUseItem(TakenItems[CurrentTakenItem]);
}

bool UTakeComponent::IsCurrentItemValidForUse()
{
	if(CurrentTakenItem == -1)
		return false;

	if(!TakenItems[CurrentTakenItem]->Implements<UUseInterface>())
		return false;
		
	return true;
}

bool UTakeComponent::CanUseItem(AActor* Item)
{
	return IUseInterface::Execute_CanUse(Item);
}
