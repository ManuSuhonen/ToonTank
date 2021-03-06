// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"


void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    

    //UE_LOG(LogTemp,Warning,TEXT("enemies: %i"),EnemyCount);

    HandleGameStart();
}

void ATankGameModeBase::HandleGameStart() 
{
    EnemyCount = GetEnemyCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this,0));
    GameStart();
    if(PlayerControllerRef != nullptr) 
    {
        PlayerControllerRef->SetPlayerEnabled(false);

        FTimerHandle EnableHandle;
        FTimerDelegate EnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,&APlayerControllerBase::SetPlayerEnabled,true);

        GetWorld()->GetTimerManager().SetTimer(EnableHandle,EnableDelegate,StartDelay,false);
    }

}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetEnemyCount() 
{
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),APawnTurret::StaticClass(),Turrets);
    return Turrets.Num();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    
    if(DeadActor == PlayerTank)
    {
        PlayerTank->OnDestruct();
        HandleGameOver(false);
        if(PlayerControllerRef != nullptr) PlayerControllerRef->SetPlayerEnabled(false);
    }

    else if(auto turret = Cast<APawnTurret>(DeadActor))
    {
        turret->OnDestruct();
        EnemyCount--;
        if(EnemyCount == 0)
        {
            HandleGameOver(true);
        }
    }
    //UE_LOG(LogTemp,Warning,TEXT("enemies: %i"),EnemyCount);
    //UE_LOG(LogTemp,Warning,TEXT("%s died"),*DeadActor->GetName());
    //DeadActor->Destroy();
}

