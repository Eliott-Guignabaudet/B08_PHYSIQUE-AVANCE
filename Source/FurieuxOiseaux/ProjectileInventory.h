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
	UFUNCTION(BlueprintCallable)
	void UseProjectileByClass(TSubclassOf<AActor> ProjectileValue);
	UFUNCTION(BlueprintCallable)
	void UseProjectileByIndex(int ProjectileIndex);
	UFUNCTION(BlueprintCallable)
	int GetNextProjectileIndex(int Index);
	UFUNCTION(BlueprintCallable)
	int GetPreviousProjectileIndex(int Index);
	UFUNCTION(BlueprintCallable)
	TSubclassOf<AActor> GetProjectileToInstantiateByIndex(int Index);
	UFUNCTION(BlueprintCallable)
	bool CanUseProjectileAtIndex(int Index);

	UFUNCTION(BlueprintCallable)
	void ClearInventory();

	
};
