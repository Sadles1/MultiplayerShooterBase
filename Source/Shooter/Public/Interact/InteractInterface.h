﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UINTERFACE()
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};


class SHOOTER_API IInteractInterface
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintNativeEvent)
	bool CanInteract(AController* Controller);
	UFUNCTION(BlueprintNativeEvent)
	void Interact(AController* Controller);
};