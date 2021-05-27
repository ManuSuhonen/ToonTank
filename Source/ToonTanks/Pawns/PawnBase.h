// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;


UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	USceneComponent* BulletSpawnPoint; 

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Projectile Type",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> Projectile;

public:
	// Sets default values for this pawn's properties
	APawnBase();
	virtual void OnDestruct();
protected:

	// handles turret rotation.
	void RotateTurretFunc(FVector Target);

	void Fire();

	// handles destruction.
	
};
