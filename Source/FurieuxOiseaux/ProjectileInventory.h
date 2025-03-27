// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FProjectileInventoryValue.h"
#include "ProjectileInventory.generated.h"
/**
 * 
 */
UCLASS()
class FURIEUXOISEAUX_API UProjectileInventory : public UObject
{
	GENERATED_BODY()

	UProjectileInventory();
	
	TArray<FProjectileInventoryValue> InventoryValues;

public:
	UFUNCTION(BlueprintCallable)
	int AddProjectile(FProjectileInventoryValue ProjectileValue);
	void UseProjectile(TSubclassOf<AActor> ProjectileValue);
	void UseProjectile(int ProjectileIndex);
	int GetNextProjectileIndex(int Index);
	int GetPreviousProjectileIndex(int Index);
	TSubclassOf<AActor> GetProjectileToInstantiateByIndex(int Index);
	bool CanUseProjectileAtIndex(int Index);
	
};
