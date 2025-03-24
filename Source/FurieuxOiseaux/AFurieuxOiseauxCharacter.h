// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AFurieuxOiseauxCharacter.generated.h"

UCLASS()
class FURIEUXOISEAUX_API AAFurieuxOiseauxCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAFurieuxOiseauxCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetProjectileDirection(FVector2D vectorValue);

	UFUNCTION(BlueprintCallable)
	void SetProjectileForce(float floatValue);

	UFUNCTION(BlueprintCallable)
	void LaunchProjectile();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
