// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UseInterface.generated.h"

UINTERFACE()
class UUseInterface : public UInterface
{
	GENERATED_BODY()
};

class SHOOTER_API IUseInterface
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent)
	bool CanUse();

	UFUNCTION(BlueprintNativeEvent)
	void StartUse();

	UFUNCTION(BlueprintNativeEvent)
	void StopUse();
};
