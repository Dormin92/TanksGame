// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLEGROUNDS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40800000;

private:
	void DriveTrack(float CurrentThrottle);
	UTankTrack();
	TArray<ASprungWheel*> GetWheels() const;
};
