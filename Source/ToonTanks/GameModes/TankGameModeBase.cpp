// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay() 
{
    
}

void ATankGameModeBase::HandleGameStart() 
{
    
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    
}

void ATankGameModeBase::ActorDiead(AActor* DeadActor) 
{
    UE_LOG(LogTemp,Warning,TEXT("%s died"),*DeadActor->GetName());
}

