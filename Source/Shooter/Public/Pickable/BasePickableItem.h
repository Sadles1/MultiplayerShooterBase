// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UseInterface.h"
#include "GameFramework/Actor.h"


#include "Interact/InteractInterface.h"


#include "BasePickableItem.generated.h"

UCLASS(Abstract)
class SHOOTER_API ABasePickableItem : public AActor, public IInteractInterface, public IUseInterface
{
	GENERATED_BODY()

public:
	
	ABasePickableItem();

	
protected:

	virtual void BeginPlay() override;

	virtual bool CanInteract_Implementation(AController* Controller) override;
	virtual void Interact_Implementation(AController* Controller) override;

	virtual void Use_Implementation() override;
	virtual bool CanUse_Implementation() override;
	
};
