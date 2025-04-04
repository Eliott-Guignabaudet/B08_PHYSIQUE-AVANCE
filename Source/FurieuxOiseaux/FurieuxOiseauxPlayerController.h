// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FurieuxOiseauxPawn.h"
#include "EnhancedInputSubsystemInterface.h"
#include "ProjectilePawn.h"
#include "GameFramework/PlayerController.h"
#include "FurieuxOiseauxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FURIEUXOISEAUX_API AFurieuxOiseauxPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	void AddMappingContextToPlayer(TObjectPtr<UInputMappingContext> Context);
protected:
	float TimeToWaitForStartAiming;
	TObjectPtr<AFurieuxOiseauxPawn> MainCharacter;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> GameplayInputMapping;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AdditionalProjectileInputMapping;
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	
	void OnLaunchProjectileCallback(TObjectPtr<AActor> Projectile);
	UFUNCTION()
	void OnProjectilePawnFinishRunCallback(AProjectilePawn* Projectile);
};
