// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pickable/TakeInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class SHOOTER_API ABaseCharacter : public ACharacter, public ITakeInterface
{
	GENERATED_BODY()

public:

	ABaseCharacter();

	
protected:

	virtual void BeginPlay() override;
	virtual UTakeComponent* GetTakeComponent() override;
	
	
private:

	UPROPERTY(VisibleDefaultsOnly)
	UTakeComponent* TakeComponent = nullptr;
};
