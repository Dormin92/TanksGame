// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLEGROUNDS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float DegreesPerSeconds);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20; //Sensible default
};
