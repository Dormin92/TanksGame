// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Aimstate Enum
UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading
};

//forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEGROUNDS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//methods
	void AimAt(FVector HitLocation);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = Controls)
	void Fire();

protected:
	//methods
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//variables
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	EFiringStatus FiringStatus = EFiringStatus::Aiming;
		
private:
	//methods
	UTankAimingComponent();
	void MoveBarrelTowards(FVector AimDirection);

	//object references and pointers
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	//variables
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 6000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

};
