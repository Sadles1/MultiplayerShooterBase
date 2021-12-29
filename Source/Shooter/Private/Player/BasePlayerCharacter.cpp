// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerCharacter.h"


#include "Camera/CameraComponent.h"


ABasePlayerCharacter::ABasePlayerCharacter()
{
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);

	FirstPersonCamera->SetFieldOfView(110.f);
	FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	
}

void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(FirstPersonCamera);
		
}


void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePlayerCharacter::OnDeath_Implementation()
{
	Super::OnDeath_Implementation();
}

void ABasePlayerCharacter::Server_StartUseCurrentItem_Implementation()
{
	GetTakeComponent()->StartUseCurrentItem();
}

void ABasePlayerCharacter::Server_StopUseCurrentItem_Implementation()
{
	GetTakeComponent()->StopUseCurrentItem();
}
