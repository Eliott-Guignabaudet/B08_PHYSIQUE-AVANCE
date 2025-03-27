// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketProjectile.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

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

	RotatingMovementLocalComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement Local"));
	RotatingMovementLocalComponent->bRotationInLocalSpace = true;
	RotatingMovementLocalComponent->RotationRate = FRotator::ZeroRotator;

	RotatingMovementWorldComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement World"));
	RotatingMovementWorldComponent->bRotationInLocalSpace = false;
	RotatingMovementWorldComponent->RotationRate = FRotator::ZeroRotator;
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
	LaunchedForce = ForceValue;
	FloatingPawnMovement->MaxSpeed *= LaunchedForce;

	bIsLaunched = true;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Process launch");
	}
}

// Called every frame
void ARocketProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsLaunched)
	{
		return;	
	}
	if (FloatingPawnMovement)
	{
		FloatingPawnMovement->AddInputVector(this->GetActorForwardVector() * ForceMultiplier * DeltaTime * LaunchedForce, true);
	}

}

// Called to bind functionality to input
void ARocketProjectile::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(RotatingInputAction, ETriggerEvent::Triggered, this , &ARocketProjectile::Rotating);
	Input->BindAction(RotatingInputAction, ETriggerEvent::Canceled, this , &ARocketProjectile::Rotating);
	Input->BindAction(RotatingInputAction, ETriggerEvent::Completed, this , &ARocketProjectile::Rotating);
}



void ARocketProjectile::PredictTrajectory_Implementation(FVector DirectionValue, float ForceValue)
{
	Super::PredictTrajectory(DirectionValue, ForceValue);
}

UPawnMovementComponent* ARocketProjectile::GetMovementComponent() const
{
	return FloatingPawnMovement;
}

void ARocketProjectile::Rotating(const FInputActionInstance& Instance)
{
	FVector2D RotatingValue = Instance.GetValue().Get<FVector2D>();
	if (RotatingMovementLocalComponent)
	{
		RotatingMovementLocalComponent->RotationRate.Pitch = -RotatingValue.Y * GetWorld()->DeltaTimeSeconds * RotationMultiplier;
	}
	if (RotatingMovementWorldComponent)
	{
		RotatingMovementWorldComponent->RotationRate.Yaw = RotatingValue.X * GetWorld()->DeltaTimeSeconds * RotationMultiplier;
	}
}

void ARocketProjectile::Explode(const FInputActionInstance& Instance)
{
	
}

