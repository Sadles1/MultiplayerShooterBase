// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"
#include "Interact/InteractInterface.h"


#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


ABasePlayerController::ABasePlayerController() { }

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

UTakeComponent* ABasePlayerController::GetTakeComponent()
{
	return Cast<ITakeInterface>(GetPawn())->GetTakeComponent();
}

bool ABasePlayerController::TryInteract()
{
	check(GetLocalRole() == ROLE_Authority)

	FHitResult HitResult;
	TraceForwardDirection(500.f, HitResult);

	if (!HitResult.bBlockingHit)
		return false;

	AActor* HitActor = HitResult.GetActor();
	if (!HitActor)
		return false;

	if (HitActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		if (IInteractInterface::Execute_CanInteract(HitActor, this))
		{
			IInteractInterface::Execute_Interact(HitActor, this);
			return true;
		}

	return false;
}

void ABasePlayerController::Server_Interact_Implementation()
{
	TryInteract();
}

void ABasePlayerController::TraceForwardDirection(float Distance, FHitResult& HitResult) const
{
	const FVector ActorLocation = PlayerCameraManager->GetCameraLocation();
	const FRotator ActorRotation = GetControlRotation();

	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ActorRotation);
	
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		ActorLocation,
		ActorLocation + ForwardVector * Distance,
		TraceTypeQuery1,
		false,
		{GetOwner()},
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
	);
}
