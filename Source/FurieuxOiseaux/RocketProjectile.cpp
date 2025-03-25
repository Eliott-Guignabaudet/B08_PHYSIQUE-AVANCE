// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketProjectile.h"

#include "Components/CapsuleComponent.h"


// Sets default values
ARocketProjectile::ARocketProjectile()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARocketProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARocketProjectile::ProcessLaunch(FVector DirectionValue, float ForceValue)
{
	Super::ProcessLaunch(DirectionValue, ForceValue);

	if (!CapsuleComponent)
	{
		return;
	}
	CapsuleComponent->AddImpulse(DirectionValue * ForceValue * ForceMultiplier);
}

// Called every frame
void ARocketProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARocketProjectile::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



void ARocketProjectile::PredictTrajectory(FVector DirectionValue, float ForceValue)
{
	Super::PredictTrajectory(DirectionValue, ForceValue);
}

