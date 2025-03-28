#pragma once


#include "CoreMinimal.h"
#include "FProjectileInventoryValue.generated.h"

USTRUCT(BlueprintType)
struct FProjectileInventoryValue
{
	GENERATED_BODY()
	
	FProjectileInventoryValue();
	FProjectileInventoryValue(TSubclassOf<AActor> ClassToInstantiate, int NumberValue);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ClassToInstantiate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
};
