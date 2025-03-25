// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "FurieuxOiseauxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FURIEUXOISEAUX_API AFurieuxOiseauxPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> GameplayInputMapping;
public:
	
	virtual void OnPossess(APawn* InPawn) override;
};
