// Fill out your copyright notice in the Description page of Project Settings.


#include "FurieuxOiseauxPlayerController.h"
#include "EnhancedInputSubsystems.h"

void AFurieuxOiseauxPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!GameplayInputMapping.IsNull())
			{
				InputSystem->AddMappingContext(GameplayInputMapping, 0);
			}
		}
	}
}
