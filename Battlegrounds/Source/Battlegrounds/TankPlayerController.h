// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEGROUNDS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	ATank* GetControlledTank() const;

	virtual void Tick(float DeltaSeconds) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	virtual void BeginPlay() override;
};

