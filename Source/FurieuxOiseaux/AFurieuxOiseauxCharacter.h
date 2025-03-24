// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "AFurieuxOiseauxCharacter.generated.h"

UCLASS()
class FURIEUXOISEAUX_API AAFurieuxOiseauxCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	FVector2D CurrentAimingValue;
	float CurrentForceValue;
	bool bIsAiming;
	TObjectPtr<AActor> CurrentAimingProjectile;
	
#pragma region Properties
	
	UPROPERTY(EditAnywhere)
	float AimingSpeed;
	UPROPERTY(EditAnywhere)
	float UpdateForceSpeed;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditDefaultsOnly)
	float ProjectileRangeRadiusPosition;
	
#pragma endregion

#pragma region Components
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> ProjectileInstantiationPosition;
	UPROPERTY(Category=Character,  VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
#pragma endregion

#pragma region Input Actions
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AimingInputAction;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> UpdateForceInputAction;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LaunchingInputAcion;
#pragma endregion
	
public:
	// Sets default values for this character's properties
	AAFurieuxOiseauxCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Aiming(const FInputActionInstance& Instance);
	void ManageForce(const FInputActionInstance& Instance);
	void LaunchProjectile(const FInputActionInstance& Instance);
	

	void StartAiming();
	void StopAiming();

private:
	void UpdateProjectilePosition();
};
