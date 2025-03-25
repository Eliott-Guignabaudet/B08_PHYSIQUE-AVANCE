// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "FurieuxOiseauxPawn.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLaunchDelegate, TObjectPtr<AActor>)

class UCameraComponent;
class UArrowComponent;

UCLASS()
class FURIEUXOISEAUX_API AFurieuxOiseauxPawn : public APawn
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
	UPROPERTY(EditDefaultsOnly)
	float ProjectileMaxBackDistance;
	
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
	AFurieuxOiseauxPawn();


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

	UFUNCTION(BlueprintImplementableEvent)
	void OnAiming(FVector2D AimingValue);
	UFUNCTION(BlueprintImplementableEvent)
	void OnManageForce(float ForceValue);
	UFUNCTION(BlueprintImplementableEvent)
	void OnLaunchProjectile(AActor* LaunchedProjectile);

	
	FOnLaunchDelegate OnLaunchProejectileDelegate;
	
	void StartAiming();
	void StopAiming();

	UFUNCTION(BlueprintPure)
	FVector GetProjectileDirection();
private:
	void UpdateProjectilePosition();
	
};
