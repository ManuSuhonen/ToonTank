// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"



// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	projectileMesh->OnComponentHit.AddDynamic(this,&AProjectileBase::OnHit);
	RootComponent = projectileMesh;

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Effect"));
	TrailEffect->SetupAttachment(RootComponent);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	projectileMovement->InitialSpeed = Speed;
	projectileMovement->MaxSpeed = Speed;
	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation());
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	AActor* MyOwner = GetOwner();
	if(!MyOwner) return;

	if(OtherActor && OtherActor != this && MyOwner != OtherActor)
	{
		//UE_LOG(LogTemp,Warning,TEXT("hit detected."));
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, MyOwner->GetInstigatorController(), this, DamageType);
	}

	UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, GetActorLocation());

	Destroy();
}
