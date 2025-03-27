#include "FProjectileInventoryValue.h"

FProjectileInventoryValue::FProjectileInventoryValue()
{
	this->ClassToInstantiate = nullptr;
	this->NumberValue = 0;
}

FProjectileInventoryValue::FProjectileInventoryValue(TSubclassOf<AActor> ClassToInstantiate, int NumberValue)
{
	this->ClassToInstantiate = ClassToInstantiate;
	this->NumberValue = NumberValue;
}
