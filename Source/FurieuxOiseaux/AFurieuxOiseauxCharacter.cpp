// Fill out your copyright notice in the Description page of Project Settings.


#include "AFurieuxOiseauxCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "UniversalObjectLocators/UniversalObjectLocatorUtils.h"
// Sets default values
AAFurieuxOiseauxCharacter::AAFurieuxOiseauxCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	ProjectileInstantiationPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	
	ProjectileInstantiationPosition->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AAFurieuxOiseauxCharacter::BeginPlay()
{
	Super::BeginPlay();
	StartAiming();
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
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(AimingInputAction, ETriggerEvent::Triggered, this, &AAFurieuxOiseauxCharacter::Aiming);
	Input->BindAction(UpdateForceInputAction, ETriggerEvent::Triggered, this, &AAFurieuxOiseauxCharacter::ManageForce);
	Input->BindAction(LaunchingInputAcion, ETriggerEvent::Completed, this, &AAFurieuxOiseauxCharacter::LaunchProjectile);
}

void AAFurieuxOiseauxCharacter::Aiming(const FInputActionInstance& Instance)
{
	if (!bIsAiming)
	{
		return;
	}
	FVector2D vectorValue = Instance.GetValue().Get<FVector2D>();
	if (vectorValue.Length() > 1)
	{
		vectorValue.Normalize();
	}

	
	CurrentAimingValue += vectorValue * GetWorld()->DeltaTimeSeconds * AimingSpeed;
	if (CurrentAimingValue.Length() > 1)
	{
		CurrentAimingValue.Normalize();
	}
	UpdateProjectilePosition();
	UE_LOG(LogTemp, Display, TEXT("Set Projectile Direction: %s"), *CurrentAimingValue.ToString());
	if (GEngine)
	{
		auto message= FString::Printf(TEXT("Set Projectile Direction: %s"), *CurrentAimingValue.ToString());
		GEngine->AddOnScreenDebugMessage(654, 2.0f, FColor::Cyan,message);
	}
	OnAiming(CurrentAimingValue);
}

void AAFurieuxOiseauxCharacter::ManageForce(const FInputActionInstance& Instance)
{
	if (!bIsAiming)
	{
		return;
	}
	float inputValue = Instance.GetValue().Get<float>();
	CurrentForceValue += inputValue * GetWorld()->GetDeltaSeconds() * UpdateForceSpeed;
	CurrentForceValue = FMath::Clamp(CurrentForceValue, 0,1);
	UpdateProjectilePosition();
	UE_LOG(LogTemp, Display, TEXT("Managing Force"));
	OnManageForce(CurrentForceValue);
}

void AAFurieuxOiseauxCharacter::LaunchProjectile(const FInputActionInstance& Instance)
{
	if (!bIsAiming)
	{
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Launching Projectile"));
}

void AAFurieuxOiseauxCharacter::StartAiming()
{
	bIsAiming = true;
	if (ProjectileClass)
	{
		CurrentAimingProjectile =UE::UniversalObjectLocator::SpawnActorForLocator(GetWorld(), ProjectileClass, TEXT("Projectile"));
		CurrentAimingProjectile->SetActorLocation(ProjectileInstantiationPosition->GetComponentLocation());
	}
}

void AAFurieuxOiseauxCharacter::StopAiming()
{
	bIsAiming = false;
	if (true)
	{
		
	}
}

void AAFurieuxOiseauxCharacter::UpdateProjectilePosition()
{
	FVector newLocation = ProjectileInstantiationPosition->GetComponentLocation();
	newLocation.Y += CurrentAimingValue.X * ProjectileRangeRadiusPosition;
	newLocation.Z += CurrentAimingValue.Y * ProjectileRangeRadiusPosition;
	newLocation.X -= CurrentForceValue * ProjectileMaxBackDistance;
	CurrentAimingProjectile->SetActorLocation(newLocation);
}

