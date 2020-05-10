// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (AmmoCount < 1)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto TargetLocation = HitLocation;
	FVector OutLaunchVelocity(0);

	if (!ensure(Barrel)) { return; }
	FVector StartLocation = Barrel->GetSocketLocation(FName("FireLocation"));

	auto ThisTank = GetOwner()->GetName();

	bool BHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, TargetLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if (!BHaveAimSolution) { return; }
	AimDirection = OutLaunchVelocity.GetSafeNormal();

	MoveBarrelTowards(AimDirection);
}

bool UTankAimingComponent::HaveLineOfSight(FVector HitLocation, AActor* Player)
{
	auto TargetLocation = HitLocation;
	FHitResult OutHit;

	if (!ensure(Barrel)) { return false; }
	FVector StartLocation = Barrel->GetSocketLocation(FName("FireLocation"));	

	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, TargetLocation, ECollisionChannel::ECC_PhysicsBody))
	{
		if (OutHit.GetActor() == Player) { return true; }
	}
	return false;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	auto AimAsRotator = AimDirection.Rotation();

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Yaw(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Yaw(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus != EFiringStatus::Reloading && FiringStatus != EFiringStatus::OutOfAmmo)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("FireLocation")), Barrel->GetSocketRotation(FName("FireLocation")));
		Projectile->LaunchProjectile(LaunchSpeed);
		AmmoCount--;
		LastFireTime = FPlatformTime::Seconds();
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelDirection = Barrel->GetForwardVector().GetSafeNormal();
	if (!AimDirection.Equals(BarrelDirection, 0.01))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int UTankAimingComponent::GetAmmoCount()
{
	return AmmoCount;
}

