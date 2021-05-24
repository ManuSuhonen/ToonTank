// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    PlayerTank = Cast<APawnTank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if(!PlayerTank)
    {
        UE_LOG(LogTemp,Error,TEXT("Tank not in scene"));
    }
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle,this,&APawnTurret::FireCondition,FireRate,true);
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APawnTurret::FireCondition() 
{
    if(!PlayerTank) return;

    float dist = DistToPlayer();
    
    if(dist <= FireRange)
    {
        UE_LOG(LogTemp,Display,TEXT("distance from enemy turret to player: %f"),dist);

    }

}

float APawnTurret::DistToPlayer() 
{
    if(!PlayerTank) return 0.f;

    return FVector::Dist(PlayerTank->GetActorLocation(),GetActorLocation());
}
