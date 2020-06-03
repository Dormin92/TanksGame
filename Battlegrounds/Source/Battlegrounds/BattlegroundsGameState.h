// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BattlegroundsGameState.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEGROUNDS_API ABattlegroundsGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	int EnemyCount = 4;
	
};
