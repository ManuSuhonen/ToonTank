// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"


class APawnTurret;
class APawnTank;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	APawnTank* PlayerTank;
	int32 EnemyCount = 0;
	TArray<AActor*> Turrets;

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

	int32 GetEnemyCount();

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

};
