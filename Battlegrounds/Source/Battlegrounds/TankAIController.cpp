// Fill out your copyright notice in the Description page of Project Settings.


#include "Battlegrounds.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (ensure(PlayerTank))
	{
		auto PlayerLocation = PlayerTank->GetActorLocation();
		PlayerLocation = PlayerLocation + FVector(0.0, 0.0, 100.0);
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimingComponent->AimAt(PlayerLocation);
		AimingComponent->HaveLineOfSight(PlayerLocation, PlayerTank);
		if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
		{
			if (AimingComponent->HaveLineOfSight(PlayerLocation, PlayerTank))
			{
				AimingComponent->Fire();
			}
		}
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	ATankPlayerController* PlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->DecrementEnemyCount();
	GetPawn()->DetachFromControllerPendingDestroy();
}
