// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret: public APawnBase
{
	GENERATED_BODY()

private:
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI Control",meta = (AllowPrivateAccess = "true"))
	float FireRate =2;
	
	void FireCondition();
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
};
