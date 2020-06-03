// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "TankAimingComponent.h"
#include "Battlegrounds.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!ensure(GetPawn())) { return; }
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation;/// Out parameter
	if (GetSightRayHitLocation(OutHitLocation))
		AimingComponent->AimAt(OutHitLocation);
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

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::DecrementEnemyCount()
{
	EnemyCount--;
	if (EnemyCount <= 0)
	{
		ConsoleCommand("quit");
	}
}
