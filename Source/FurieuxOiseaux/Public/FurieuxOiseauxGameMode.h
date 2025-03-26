// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FurieuxOiseauxGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FURIEUXOISEAUX_API AFurieuxOiseauxGameMode : public AGameModeBase
{
	GENERATED_BODY()

	int m_totalScore = 0;
};
