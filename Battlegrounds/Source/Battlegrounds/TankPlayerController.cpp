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
	auto ControlledTank = GetControlledTank();
	APlayerCameraManager* CameraManager = PlayerCameraManager;
	FVector Start = CameraManager->GetCameraLocation();
	FVector End = CameraManager->GetActorForwardVector() * 75000;
	End = Start + End;
	UE_LOG(LogTemp, Warning, TEXT("End vector is: %s"), *End.ToString());
	FRotator Adjustment = FRotator(8.0f, 0.0f, 0.0f);
	End = Adjustment.RotateVector(End);

	DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor(255, 0, 0),
		false, -1, 0,
		12.333
	);

	return true;
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