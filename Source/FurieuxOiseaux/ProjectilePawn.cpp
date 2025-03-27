// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePawn.h"


// Sets default values
AProjectilePawn::AProjectilePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProjectilePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectilePawn::ProcessLaunch(FVector DirectionValue, float ForceValue)
{
}

// Called every frame
void AProjectilePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AProjectilePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AProjectilePawn::Launch_Implementation(FVector DirectionValue, float ForceValue)
{
	ProcessLaunch(DirectionValue, ForceValue);
	
	OnLaunchProjectileDelegate.Broadcast();
}

