// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float BaseDamage,const UDamageType* DamageType ,AController* Instigator, AActor* DamageCauser) 
{
	if(BaseDamage == 0) return;

	Health = FMath::Clamp(Health - BaseDamage,0.f,DefaultHealth);

	//UE_LOG(LogTemp,Warning,TEXT("TakeDamage"));

	UE_LOG(LogTemp,Warning,TEXT("%f"),BaseDamage);

	if(Health <= 0)
	{
		if(GameModeRef)
		{
			GameModeRef->ActorDiead(GetOwner());
			//UE_LOG(LogTemp,Warning,TEXT("TakeDamage"));
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Health Component has no ref to GameMode"));
		}
	}
}

