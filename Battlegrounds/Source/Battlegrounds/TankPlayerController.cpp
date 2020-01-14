// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Battlegrounds.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;/// Out Parameters
	GetSightRayHitLocation(HitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//raycast from camera through crosshair
		//get camera location
	auto ControlledTank = GetControlledTank();
	FVector Start = PlayerCameraManager->GetTargetLocation();
	FVector End = PlayerCameraManager->GetActorForwardVector();
	End = End.RotateAngleAxis(8.0f, FVector(0.0f, 1.0f, 0.0f));
	End = End * 1000;
	DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor(255, 0, 0),
		false, -1, 0,
		12.333
	);
	return true;
		//get crosshair location
			//crosshair is always 2/3rd from the bottom of the screen
			//angle is... 8 degrees
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player not possessing any tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player possessing %s"), *ControlledTank->GetName());
	}
}