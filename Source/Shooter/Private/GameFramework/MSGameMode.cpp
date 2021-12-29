// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/MSGameMode.h"


void AMSGameMode::RespawnPlayer(AController* Controller)
{
	Controller->GetPawn()->Destroy();
	
	APawn* NewPawn = SpawnDefaultPawnFor(Controller, FindPlayerStart(Controller));
	Controller->Possess(NewPawn);
}
