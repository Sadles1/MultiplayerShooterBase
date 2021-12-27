// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"


class UCameraComponent;


UCLASS()
class SHOOTER_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	
	ABasePlayerCharacter();
	

protected:
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void Server_UseCurrentItem();

	
private:

	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* FirstPersonCamera = nullptr;

	
};
