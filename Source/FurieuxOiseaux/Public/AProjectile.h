// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USoundBase;

UCLASS()
class FURIEUXOISEAUX_API AAProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AAProjectile();
	
protected:
	virtual void BeginPlay() override;

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Mesh
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UStaticMeshComponent* MeshComponent;
	
	// Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	// Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* MovementComponent;

	// Impact Sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	USoundBase* ImpactSound;
};
