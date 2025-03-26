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
			if (Context)
			{
				InputSystem->AddMappingContext(Context, 0);
			}
		}
	}
}



void AFurieuxOiseauxPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	auto CharacterCasted = Cast<AFurieuxOiseauxPawn>(InPawn);
	if ( CharacterCasted)
	{
		MainCharacter = CharacterCasted;
		AddMappingContextToPlayer(GameplayInputMapping);
		AddMappingContextToPlayer(AdditionalProjectileInputMapping);
		MainCharacter->OnLaunchProejectileDelegate.AddUObject(this, &AFurieuxOiseauxPlayerController::OnLaunchProjectileCallback);
	}
	
	UE_LOG(LogTemp, Display, TEXT("On Possess pawn"));
	
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
