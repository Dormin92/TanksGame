// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Battlegrounds.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(PlayerTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank Found"));
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
		AimingComponent->Fire();
	}
	else{ UE_LOG(LogTemp, Warning, TEXT("PlayerTank NOT found")); }
}