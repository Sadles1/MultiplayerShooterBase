// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework\BaseCharacter.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	TakeComponent = CreateDefaultSubobject<UTakeComponent>(TEXT("TakeComponent"));
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

UTakeComponent* ABaseCharacter::GetTakeComponent()
{
	return TakeComponent;
}
