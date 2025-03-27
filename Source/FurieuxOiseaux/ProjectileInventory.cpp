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

void UProjectileInventory::UseProjectileByClass(TSubclassOf<AActor> ProjectileValue)
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

void UProjectileInventory::UseProjectileByIndex(int ProjectileIndex)
{
	if ((ProjectileIndex < 0 || ProjectileIndex > InventoryValues.Num()) || InventoryValues[ProjectileIndex].NumberValue <= 0)
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
	if (Index < 0 || Index > InventoryValues.Num())
	{
		return nullptr;
	}

	return InventoryValues[Index].ClassToInstantiate;
	
}

bool UProjectileInventory::CanUseProjectileAtIndex(int Index)
{
	if (Index < 0 || Index > InventoryValues.Num())
	{
		return false;
	}

	if (InventoryValues[Index].NumberValue <= 0)
	{
		return false;
	}

	return true;
}

void UProjectileInventory::ClearInventory()
{
	InventoryValues.Empty();
}

