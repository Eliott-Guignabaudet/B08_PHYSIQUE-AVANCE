// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileInterface.h"
#include "GameFramework/Pawn.h"
#include "ProjectilePawn.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnLaunchProjectileDelegate);

UCLASS()
class FURIEUXOISEAUX_API AProjectilePawn : public APawn, public IProjectileInterface
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnFinishRunDelegate, TObjectPtr<AProjectilePawn>);
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AProjectilePawn();
	
	FOnLaunchProjectileDelegate OnLaunchProjectileDelegate;
	FOnFinishRunDelegate OnFinishRunDelegate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ProcessLaunch(FVector DirectionValue, float ForceValue){}
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Launch(FVector DirectionValue, float ForceValue) override;
};
