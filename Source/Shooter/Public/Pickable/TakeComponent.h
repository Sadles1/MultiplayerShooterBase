// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickableItem.h"
#include "Components/ActorComponent.h"
#include "TakeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API UTakeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTakeComponent();

	bool TryTakeItem(ABasePickableItem* Item);

	bool TryUseCurrentItem();
	bool CanUseCurrentItem();

	
protected:

	virtual void BeginPlay() override;

	
private:

	UPROPERTY()
    TArray<ABasePickableItem*> TakenItems;

	UPROPERTY()
	uint32 CurrentTakenItem = -1;
	
};
