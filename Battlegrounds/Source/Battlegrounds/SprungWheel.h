// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h" 
#include "Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLEGROUNDS_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	ASprungWheel();
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* MassAxleConstraint = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupConstraints();
};
