// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
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

	FVector OutHitLocation;/// Out parameter
	if (GetSightRayHitLocation(OutHitLocation))
		GetControlledTank()->AimAt(OutHitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector TraceDirectionVector, TraceStartLocation, TraceEndLocation;

	if (GetLookDirection(ScreenLocation, TraceStartLocation, TraceDirectionVector))
	{
		TraceEndLocation = (TraceDirectionVector * LineTraceRange) + TraceStartLocation;
		FHitResult OutHit;
		if (GetWorld()->LineTraceSingleByChannel(OutHit, TraceStartLocation, TraceEndLocation, ECC_Visibility))
		{
			OutHitLocation = OutHit.Location;
			return true;
		}
	}
	OutHitLocation = FVector(0.0f);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector& CameraPosition, FVector& OutHitLocation) const
{
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraPosition, OutHitLocation);
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