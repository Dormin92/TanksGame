// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

class UTankBarrel;

UCLASS()
class BATTLEGROUNDS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category  = Firing)
	float LaunchSpeed = 100000.0f;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	ATank();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup) //Called by blueprint to assign barrel
	void SetBarrelReference(UTankBarrel* BarrelToSet);

};
