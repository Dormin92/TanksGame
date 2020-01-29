// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Yaw(float YawRotation)
{
	auto RotationChange = YawRotation * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewYaw = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, NewYaw, 0));
}
