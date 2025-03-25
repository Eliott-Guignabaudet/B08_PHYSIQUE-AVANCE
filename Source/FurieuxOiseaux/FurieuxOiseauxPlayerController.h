// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AFurieuxOiseauxCharacter.h"
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
	void AddMappingContextsToPlayer(TArray<TObjectPtr<UInputMappingContext>> Contexts);
protected:
	TObjectPtr<AAFurieuxOiseauxCharacter> MainCharacter;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> GameplayInputMapping;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AdditionalProjectileInputMapping;
public:
	
	virtual void OnPossess(APawn* InPawn) override;
	
	void OnLaunchProjectileCallback(TObjectPtr<AActor> Projectile);
	void OnProjectilePawnFinishRunCallback(TObjectPtr<AProjectilePawn> Projectile);
};
