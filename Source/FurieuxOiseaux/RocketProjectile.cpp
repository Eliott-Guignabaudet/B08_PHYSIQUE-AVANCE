// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketProjectile.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ARocketProjectile::ARocketProjectile()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponentRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SceneComponentRoot->SetupAttachment(RootComponent);
	RootComponent = SceneComponentRoot;
	SecondCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule2"));
	SecondCapsuleComponent->SetupAttachment(SceneComponentRoot);
	SecondCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));


	//CapsuleComponent->SetupAttachment(SceneComponentRoot);
	
}

// Called when the game starts or when spawned
void ARocketProjectile::BeginPlay()
{
	Super::BeginPlay();
	bIsLaunched = false;
}

void ARocketProjectile::ProcessLaunch(FVector DirectionValue, float ForceValue)
{
	Super::ProcessLaunch(DirectionValue, ForceValue);

	bIsLaunched = true;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Process launch");
	}
	UE_LOG(LogTemp, Display, TEXT("Process launch"));
	// if (!SecondCapsuleComponent)
	// {
	// 	return;
	// }
	// FRotator newRotation = DirectionValue.Rotation();
	// SecondCapsuleComponent->SetRelativeRotation(newRotation);
	// SecondCapsuleComponent->SetSimulatePhysics(true);
	// SecondCapsuleComponent->AddImpulse(DirectionValue * ForceValue * ForceMultiplier);
}

// Called every frame
void ARocketProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsLaunched)
	{
		return;	
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(214564, 2.0f, FColor::Yellow, "ADD Input Movement");
	}
	UPawnMovementComponent* MovementComponent = GetMovementComponent();
	if (MovementComponent)
	{
		MovementComponent->AddInputVector(this->GetActorForwardVector() * ForceMultiplier * DeltaTime, true);
	}

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

UPawnMovementComponent* ARocketProjectile::GetMovementComponent() const
{
	return FloatingPawnMovement;
}

