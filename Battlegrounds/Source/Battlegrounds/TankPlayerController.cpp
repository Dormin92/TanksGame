// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Battlegrounds.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
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