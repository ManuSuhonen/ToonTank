// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;


UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* projectileMovement;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* TrailEffect;

	UPROPERTY(EditDefaultsOnly,Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Projectile Speed",meta = (AllowPrivateAccess = "true"))
	float Speed = 1000;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Damage Amount",meta = (AllowPrivateAccess = "true"))
	float DamageAmount = 50;

	UPROPERTY(EditAnywhere,Category = "Effects")
	UParticleSystem* HitEffect;


	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
