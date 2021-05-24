// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle,this,&APawnTurret::FireCondition,FireRate,true);
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void APawnTurret::FireCondition() 
{
    UE_LOG(LogTemp,Display,TEXT("FireCondition!!!!!"));
}
