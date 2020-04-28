// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h" 
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
	UStaticMeshComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* PhysicsConstraint = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupConstraints();
};
