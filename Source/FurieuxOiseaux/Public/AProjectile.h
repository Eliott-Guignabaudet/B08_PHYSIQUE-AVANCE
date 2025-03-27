// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "AProjectile.generated.h"

UCLASS()
class FURIEUXOISEAUX_API AAProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AAProjectile();
	
protected:
	virtual void BeginPlay() override;

	// Root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootScene;
	
	// Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;
	
	// Mesh
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UStaticMeshComponent* MeshComponent;

	// Niagara
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* NiagaraSystem;
	
public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
			   UPrimitiveComponent* OtherComponent, FVector NormalImpulse, 
			   const FHitResult& Hit);
	
	void SpawnExplosionVFX();
};
