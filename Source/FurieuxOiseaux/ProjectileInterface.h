// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UProjectileInterface : public UInterface
{
	GENERATED_BODY()
};

class IProjectileInterface
{
	GENERATED_BODY()


public:
	virtual void Launch(FVector DirectionValue, float ForceValue);
	virtual void PredictTrajectory(FVector DirectionValue, float ForceValue);
	
};

