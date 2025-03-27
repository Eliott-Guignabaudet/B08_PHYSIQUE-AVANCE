// Fill out your copyright notice in the Description page of Project Settings.

#include "AProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "NiagaraFunctionLibrary.h"

// Sets default values
AAProjectile::AAProjectile()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootScene;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(25.0f);
	CollisionComponent->SetSimulatePhysics(true);
	// CollisionComponent->SetMassOverrideInKg(NAME_None, 10.0f);
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetCollisionProfileName("BlockAll");
	CollisionComponent->SetupAttachment(RootScene);
	
	CollisionComponent->OnComponentHit.AddDynamic(this, &AAProjectile::OnHit);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionComponent);
}

void AAProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AAProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision : %s"), *OtherActor->GetName());
	
	Destroy();

	SpawnExplosionVFX();
	
}

void AAProjectile::SpawnExplosionVFX()
{
	if (NiagaraSystem)
	{
		const FVector SpawnLocation = CollisionComponent->GetComponentLocation();
		const FRotator SpawnRotation = CollisionComponent->GetComponentRotation();
		
		const FVector SpawnScale = FVector(2.0f);
		
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, SpawnLocation, SpawnRotation, SpawnScale);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NiagaraSystemToSpawn ou NiagaraComponent n'est pas valide."));
	}
}
