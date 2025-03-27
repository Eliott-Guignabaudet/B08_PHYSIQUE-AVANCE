// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectilePawn.h"
#include "RocketProjectile.generated.h"

struct FInputActionInstance;
class URotatingMovementComponent;
class UCapsuleComponent;
class USceneComponent;
class UFloatingPawnMovement;
class UInputAction;
UCLASS()
class FURIEUXOISEAUX_API ARocketProjectile : public AProjectilePawn
{
	GENERATED_BODY()
private:
	bool bIsLaunched;

	
public:
	// Sets default values for this pawn's properties
	ARocketProjectile();
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> SecondCapsuleComponent;
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponentRoot;
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<URotatingMovementComponent> RotatingMovementLocalComponent;
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<URotatingMovementComponent> RotatingMovementWorldComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RotatingInputAction;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ExplodeInputAction;
	UPROPERTY(EditAnywhere)
	float ForceMultiplier;
	UPROPERTY(EditAnywhere)
	float RotationMultiplier;

	UPROPERTY(BlueprintReadWrite)
	float LaunchedForce;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ProcessLaunch(FVector DirectionValue, float ForceValue) override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PredictTrajectory_Implementation(FVector DirectionValue, float ForceValue) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	void Rotating(const FInputActionInstance& Instance);
	void Explode(const FInputActionInstance& Instance);
};
