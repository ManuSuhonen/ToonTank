// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret: public APawnBase
{
	GENERATED_BODY()

private:
	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerTank;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI Control",meta = (AllowPrivateAccess = "true"))
	float FireRate =2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI Control",meta = (AllowPrivateAccess = "true"))
	float FireRange = 300;
	
	void FireCondition();
	float DistToPlayer();
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
};
