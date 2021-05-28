// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));

    SpringArm->SetupAttachment(RootComponent);


    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));

    Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
    PlayerControlRef = Cast<APlayerController>(GetController());
}

void APawnTank::OnDestruct() 
{
    Super::OnDestruct();
    bIsAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    //Destroy();
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Rotate();
    Move();

    if(PlayerControlRef)
    {
        FHitResult hit;
        PlayerControlRef->GetHitResultUnderCursor(ECC_Visibility,false,hit);
        FVector hitloc = hit.ImpactPoint;

        RotateTurretFunc(hit.ImpactPoint);
    }

}

bool APawnTank::GetIsAlive() 
{
    return bIsAlive;
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward",this,&APawnTank::CalcMoveInput);
    PlayerInputComponent->BindAxis("Turn",this,&APawnTank::CalcRotateInput);

    PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&APawnTank::Fire);
}
void APawnTank::CalcMoveInput(float Val) 
{
    MoveDirection = FVector(Val* MoveSpeed * GetWorld()->DeltaTimeSeconds,0,0);
}

void APawnTank::CalcRotateInput(float Val) 
{
    float amount =  Val * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator rotation = FRotator(0,amount,0);
    RotationDirection = FQuat(rotation);
}

void APawnTank::Move() 
{
    AddActorLocalOffset(MoveDirection,true);
}

void APawnTank::Rotate() 
{
    AddActorLocalRotation(RotationDirection,true);
}
