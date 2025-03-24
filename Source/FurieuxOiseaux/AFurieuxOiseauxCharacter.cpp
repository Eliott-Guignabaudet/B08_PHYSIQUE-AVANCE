// Fill out your copyright notice in the Description page of Project Settings.


#include "AFurieuxOiseauxCharacter.h"

// Sets default values
AAFurieuxOiseauxCharacter::AAFurieuxOiseauxCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAFurieuxOiseauxCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void AAFurieuxOiseauxCharacter::SetProjectileDirection(FVector2d vectorValue)
{
	UE_LOG(LogTemp, Display, TEXT("Set Projectile Direction: %s"), *vectorValue.ToString());
}

void AAFurieuxOiseauxCharacter::SetProjectileForce(float floatValue)
{
	UE_LOG(LogTemp, Display, TEXT("Set Projectile force: %f"), floatValue);
}

void AAFurieuxOiseauxCharacter::LaunchProjectile()
{
	UE_LOG(LogTemp, Display, TEXT("Launch Projectile"));
}

// Called every frame
void AAFurieuxOiseauxCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAFurieuxOiseauxCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

