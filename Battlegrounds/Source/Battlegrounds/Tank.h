// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLEGROUNDS_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	ATank();	
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	FTankDelegate OnDeath;

	//returns current health as a percentage of max health between 0-1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

};