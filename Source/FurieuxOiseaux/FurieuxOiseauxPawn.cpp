// Fill out your copyright notice in the Description page of Project Settings.


#include "FurieuxOiseauxPawn.h"
#include "EnhancedInputComponent.h"
#include "ProjectileInterface.h"
#include "ProjectileInventory.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UniversalObjectLocators/UniversalObjectLocatorUtils.h"

// Sets default values
AFurieuxOiseauxPawn::AFurieuxOiseauxPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	CurrentProjectileIndex = 0;

	PrimaryActorTick.bCanEverTick = true;
	SceneComponentRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponentRoot;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	ProjectileInstantiationPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	
	ProjectileInstantiationPosition->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AFurieuxOiseauxPawn::BeginPlay()
{
	Super::BeginPlay();
	Inventory = NewObject<UProjectileInventory>();
	Inventory->AddProjectile(FProjectileInventoryValue(ProjectileClass, 10));

	StartAiming();
	FVector spawnLocation = ProjectileInstantiationPosition->GetComponentLocation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,"Spawn location: " + spawnLocation.ToString());
	}
}


// Called every frame
void AFurieuxOiseauxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsAiming)
	{
		if (CurrentAimingProjectile->GetClass()->ImplementsInterface(UProjectileInterface::StaticClass()))
		{
			IProjectileInterface::Execute_PredictTrajectory(CurrentAimingProjectile, GetProjectileDirection(), CurrentForceValue);
			
		}
	}
}

// Called to bind functionality to input
void AFurieuxOiseauxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(AimingInputAction, ETriggerEvent::Triggered, this, &AFurieuxOiseauxPawn::Aiming);
	Input->BindAction(UpdateForceInputAction, ETriggerEvent::Triggered, this, &AFurieuxOiseauxPawn::ManageForce);
	Input->BindAction(LaunchingInputAcion, ETriggerEvent::Started, this, &AFurieuxOiseauxPawn::LaunchProjectile);
}

void AFurieuxOiseauxPawn::Aiming(const FInputActionInstance& Instance)
{
	if (!bIsAiming)
	{
		return;
	}
	FVector2D vectorValue = Instance.GetValue().Get<FVector2D>();
	if (vectorValue.Length() > 1)
	{
		vectorValue.Normalize() ;
	}
	
	CurrentAimingValue += vectorValue * GetWorld()->DeltaTimeSeconds * AimingSpeed;

	if (CurrentAimingValue.Length() > 0.5)
	{
		CurrentAimingValue.Normalize() ;
		CurrentAimingValue *= 0.5f;
	}
	UpdateProjectilePosition();
	OnAiming(CurrentAimingValue);
}

void AFurieuxOiseauxPawn::ManageForce(const FInputActionInstance& Instance)
{
	if (!bIsAiming)
	{
		return;
	}
	float inputValue = Instance.GetValue().Get<float>();
	CurrentForceValue += inputValue * GetWorld()->GetDeltaSeconds() * UpdateForceSpeed;
	CurrentForceValue = FMath::Clamp(CurrentForceValue, 0.2,1);
	UpdateProjectilePosition();
	OnManageForce(CurrentForceValue);
}

void AFurieuxOiseauxPawn::LaunchProjectile(const FInputActionInstance& Instance)
{
	if (!bIsAiming || !Inventory->CanUseProjectileAtIndex(CurrentProjectileIndex))
	{
		return;
	}
	if (CurrentAimingProjectile->GetClass()->ImplementsInterface(UProjectileInterface::StaticClass()))
	{
		IProjectileInterface::Execute_Launch(CurrentAimingProjectile,GetProjectileDirection(), CurrentForceValue);
		UE_LOG(LogTemp, Display, TEXT("LaunchProjectile"));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, "Launching");
		}
	}

	StopAiming();
	Inventory->UseProjectileByIndex(CurrentProjectileIndex);
	OnLaunchProjectile(CurrentAimingProjectile);
	OnLaunchProejectileDelegate.Broadcast(CurrentAimingProjectile);
}

void AFurieuxOiseauxPawn::StartAiming()
{
	bIsAiming = true;
	if (Inventory)
	{
		auto classToInstantiate = Inventory->GetProjectileToInstantiateByIndex(CurrentProjectileIndex);
		if (CurrentAimingProjectile)
		{
			CurrentAimingProjectile = nullptr;
		}
		if (classToInstantiate)
		{
			CurrentAimingProjectile =UE::UniversalObjectLocator::SpawnActorForLocator(GetWorld(), classToInstantiate, TEXT("Projectile"));
			CurrentAimingProjectile->SetActorLocation(ProjectileInstantiationPosition->GetComponentLocation());
			return;
		}
		
	}

	
	if (ProjectileClass)
	{
		CurrentAimingProjectile =UE::UniversalObjectLocator::SpawnActorForLocator(GetWorld(), ProjectileClass, TEXT("Projectile"));
		CurrentAimingProjectile->SetActorLocation(ProjectileInstantiationPosition->GetComponentLocation());
	}
}

void AFurieuxOiseauxPawn::StopAiming()
{
	bIsAiming = false;
}

void AFurieuxOiseauxPawn::UpdateProjectilePosition()
{
	FVector newLocation = ProjectileInstantiationPosition->GetComponentLocation();
	float zAxis = FMath::Square(1 - (CurrentAimingValue.X *CurrentAimingValue.X + CurrentAimingValue.Y *CurrentAimingValue.Y));
	FVector AddingLocationVector = FVector(-zAxis, CurrentAimingValue.X, CurrentAimingValue.Y );

	newLocation += AddingLocationVector * CurrentForceValue * ProjectileRangeRadiusPosition;
	CurrentAimingProjectile->SetActorLocation(newLocation);
	
	CurrentAimingProjectile->SetActorRotation(GetProjectileDirection().Rotation());

	
	
}

void AFurieuxOiseauxPawn::UpdateProjectile()
{
	auto newProjectileClass = Inventory->GetProjectileToInstantiateByIndex(CurrentProjectileIndex);
	if (newProjectileClass == CurrentAimingProjectile.GetClass())
	{
		return;
	}
	

	CurrentAimingProjectile->Destroy();
	CurrentAimingProjectile =UE::UniversalObjectLocator::SpawnActorForLocator(GetWorld(), newProjectileClass, TEXT("Projectile"));
	CurrentAimingProjectile->SetActorLocation(ProjectileInstantiationPosition->GetComponentLocation());
	UpdateProjectilePosition();
	
}

FVector AFurieuxOiseauxPawn::GetProjectileDirection()
{
	float zAxis = FMath::Square(1 - (CurrentAimingValue.X *CurrentAimingValue.X + CurrentAimingValue.Y *CurrentAimingValue.Y));
	FVector Result = FVector(zAxis, -CurrentAimingValue.X, -CurrentAimingValue.Y );
	return Result;
}

