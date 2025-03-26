// Fill out your copyright notice in the Description page of Project Settings.

#include "AProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAProjectile::AAProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Création du composant de collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionProfileName("Projectile");
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AAProjectile::OnHit);
	RootComponent = CollisionComponent;

	// Activation de la simulation physique pour pouvoir définir une masse (poids)
	CollisionComponent->SetSimulatePhysics(true);
	// Définissez la masse en kilogrammes (exemple : 10kg)
	CollisionComponent->SetMassOverrideInKg(NAME_None, 10.0f);
	
	// Créez le composant mesh et l'attachez à la racine
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	// Création du composant de mouvement du projectile
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	MovementComponent->UpdatedComponent = CollisionComponent;
	MovementComponent->InitialSpeed = 0.f;
	MovementComponent->MaxSpeed = 3000.f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bShouldBounce = false;
	// Ajustez la gravité (1.0 = gravité par défaut)
	MovementComponent->ProjectileGravityScale = 1.0f;
}

void AAProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AAProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Vérifiez que l'acteur touché est valide et différent de nous-mêmes
	if (OtherActor && (OtherActor != this))
	{
		// Par exemple, on détruit le projectile uniquement si l'acteur a le tag "Destructible"
		if (OtherActor->ActorHasTag("Destructible"))
		{
			// Joue l'effet sonore à l'impact, s'il est défini
			if (ImpactSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
			}
			// Détruit le projectile
			Destroy();
		}
	}
}
