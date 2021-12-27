// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "TakeComponent.h"
#include "UObject/Interface.h"


#include "TakeInterface.generated.h"

UINTERFACE()
class UTakeInterface : public UInterface
{
	GENERATED_BODY()
};

class SHOOTER_API ITakeInterface
{
	GENERATED_BODY()
	
public:

	virtual UTakeComponent* GetTakeComponent();
	
};
