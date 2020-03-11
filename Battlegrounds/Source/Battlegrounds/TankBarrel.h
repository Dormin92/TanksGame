// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = ("Materials", "Physics", "Lighting") )
class BATTLEGROUNDS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 20;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevation = 35;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevation = 0;
};
