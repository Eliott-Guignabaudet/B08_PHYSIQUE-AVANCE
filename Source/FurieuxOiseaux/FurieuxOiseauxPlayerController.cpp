// Fill out your copyright notice in the Description page of Project Settings.


#include "FurieuxOiseauxPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "ProjectilePawn.h"

void AFurieuxOiseauxPlayerController::AddMappingContextToPlayer(TObjectPtr<UInputMappingContext> Context)
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (GameplayInputMapping)
			{
				InputSystem->AddMappingContext(Context, 0);
			}
		}
	}
}



void AFurieuxOiseauxPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	auto CharacterCasted = Cast<AAFurieuxOiseauxCharacter>(InPawn);
	if ( CharacterCasted)
	{
		MainCharacter = CharacterCasted;
		AddMappingContextToPlayer(GameplayInputMapping);
		AddMappingContextToPlayer(AdditionalProjectileInputMapping);
		MainCharacter->OnLaunchProejectileDelegate.AddUObject(this, &AFurieuxOiseauxPlayerController::OnLaunchProjectileCallback);
	}
	

	
}

void AFurieuxOiseauxPlayerController::OnLaunchProjectileCallback(TObjectPtr<AActor> Projectile)
{
	TObjectPtr<AProjectilePawn> ProjectileCasted = Cast<AProjectilePawn>(Projectile);
	if (ProjectileCasted)
	{
		UnPossess();
		Possess(ProjectileCasted);
		ProjectileCasted->OnFinishRunDelegate.AddUObject(this, &AFurieuxOiseauxPlayerController::OnProjectilePawnFinishRunCallback);
	}
}

void AFurieuxOiseauxPlayerController::OnProjectilePawnFinishRunCallback(TObjectPtr<AProjectilePawn> Projectile)
{
	if (GetPawn() != Projectile)
	{
		return;
	}
	UnPossess();
	if (MainCharacter)
	{
		Possess(MainCharacter);
	}
}
