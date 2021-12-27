// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UPickupComponent();
	bool TryPickItem(AController* Controller);

protected:
	
	virtual void BeginPlay() override;

	
private:

	
	
};
