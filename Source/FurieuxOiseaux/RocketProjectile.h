// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectilePawn.h"
#include "RocketProjectile.generated.h"

class UCapsuleComponent;


UCLASS()
class FURIEUXOISEAUX_API ARocketProjectile : public AProjectilePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARocketProjectile();
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere)
	float ForceMultiplier;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ProcessLaunch(FVector DirectionValue, float ForceValue) override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PredictTrajectory(FVector DirectionValue, float ForceValue) override;
};
