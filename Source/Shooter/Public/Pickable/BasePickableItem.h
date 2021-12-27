// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupComponent.h"
#include "GameFramework/Actor.h"


#include "Interact/InteractInterface.h"


#include "BasePickableItem.generated.h"

UCLASS(Abstract)
class SHOOTER_API ABasePickableItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	
	ABasePickableItem();

	
protected:

	virtual void BeginPlay() override;

	virtual bool CanInteract_Implementation(AController* Controller) override;
	virtual void Interact_Implementation(AController* Controller) override;

private:

	UPROPERTY()
	UPickupComponent* PickupComponent = nullptr;
};
