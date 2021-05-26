// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = Capsule;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);


	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));
	BulletSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::RotateTurretFunc(FVector Target) 
{
	FVector cleaned = FVector(Target.X,Target.Y,TurretMesh->GetComponentLocation().Z);
	FVector start = TurretMesh->GetComponentLocation();

	FRotator rotation = FVector(cleaned - start).Rotation();

	TurretMesh->SetWorldRotation(rotation);
}

void APawnBase::Fire() 
{
	//UE_LOG(LogTemp,Warning,TEXT("Shell Fired."));

	if(Projectile)
	{
		AProjectileBase* temp = GetWorld()->SpawnActor<AProjectileBase>(Projectile,BulletSpawnPoint->GetComponentLocation(),BulletSpawnPoint->GetComponentRotation());
		temp->SetOwner(this);
	}
}

void APawnBase::OnDestruct() 
{
	
}


