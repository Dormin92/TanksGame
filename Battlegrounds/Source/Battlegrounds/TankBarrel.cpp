// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	//do this rotation over deltatime
	UE_LOG(LogTemp, Warning, TEXT("Rotating by %s degrees"), DegreesPerSecond);
}