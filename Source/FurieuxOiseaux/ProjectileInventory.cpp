// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileInventory.h"

UProjectileInventory::UProjectileInventory()
{
}

int UProjectileInventory::AddProjectile(FProjectileInventoryValue ProjectileValue)
{
	for (int i = 0; i < InventoryValues.Num(); i++)
	{
		if (ProjectileValue.ClassToInstantiate == InventoryValues[i].ClassToInstantiate)
		{
			
			InventoryValues.GetData()->NumberValue += ProjectileValue.NumberValue;
			return i;
		}
	}

	InventoryValues.Add(ProjectileValue);
	return InventoryValues.Num() - 1;
}

void UProjectileInventory::UseProjectile(TSubclassOf<AActor> ProjectileValue)
{
	for (int i = 0; i < InventoryValues.Num(); i++)
	{
		if (ProjectileValue == InventoryValues[i].ClassToInstantiate && InventoryValues[i].NumberValue > 0)
		{
			InventoryValues.GetData()->NumberValue --;
			return;
		}
	}
}

void UProjectileInventory::UseProjectile(int ProjectileIndex)
{
	if (!InventoryValues.IsValidIndex(ProjectileIndex) || InventoryValues[ProjectileIndex].NumberValue <= 0)
	{
		return;
	}
	InventoryValues.GetData()->NumberValue --;
}

int UProjectileInventory::GetNextProjectileIndex(int Index)
{
	if (Index == InventoryValues.Num() -1)
	{
		return 0;
	}
	return Index+1;
}

int UProjectileInventory::GetPreviousProjectileIndex(int Index)
{
	if (Index == 0)
	{
		return InventoryValues.Num() -1;
	}
	return Index - 1;
}

TSubclassOf<AActor> UProjectileInventory::GetProjectileToInstantiateByIndex(int Index)
{
	if (InventoryValues.IsValidIndex(Index))
	{
		return InventoryValues[Index].ClassToInstantiate;
	}
	return nullptr;
}

bool UProjectileInventory::CanUseProjectileAtIndex(int Index)
{
	if (!InventoryValues.IsValidIndex(Index))
	{
		return false;
	}

	if (InventoryValues[Index].NumberValue <= 0)
	{
		return false;
	}

	return true;
}
