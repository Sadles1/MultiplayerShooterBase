// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TakeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API UTakeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTakeComponent();

	bool TryTakeItem(AActor* Item);

	void StartUseCurrentItem();
	void StopUseCurrentItem();
	
	bool CanUseCurrentItem();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SwitchCurrentItem(int32 NewItem);

	
protected:

	virtual void BeginPlay() override;

	bool IsCurrentItemValidForUse();
	bool CanUseItem(AActor* Item);

	void SetCurrentTakenItem(int8 NewItem);

	void SwitchCurrentItem(int8 NewItem);
	
private:

	UPROPERTY()
    TArray<AActor*> TakenItems;

	UPROPERTY()
	int8 CurrentTakenItem = -1;
	
};
