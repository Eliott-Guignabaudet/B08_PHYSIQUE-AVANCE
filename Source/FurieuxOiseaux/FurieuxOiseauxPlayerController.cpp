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


void AFurieuxOiseauxPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (TimeToWaitForStartAiming <= 0)
	{
		return;
	}
	TimeToWaitForStartAiming -= DeltaSeconds;
	if (TimeToWaitForStartAiming <= 0)
	{
		TimeToWaitForStartAiming = 0;
		if (MainCharacter)
		{
			MainCharacter->StartAiming();
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
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("On Possess pawn"));
	
}

void AFurieuxOiseauxPlayerController::OnLaunchProjectileCallback(TObjectPtr<AActor> Projectile)
{
	if (GetPawn() == Projectile)
	{
		return;
	}
	TObjectPtr<AProjectilePawn> ProjectileCasted = Cast<AProjectilePawn>(Projectile);
	if (ProjectileCasted)
	{
		UnPossess();
		Possess(ProjectileCasted);
		ProjectileCasted->OnFinishRunDelegate.AddDynamic(this, &AFurieuxOiseauxPlayerController::OnProjectilePawnFinishRunCallback);
		return;
	}
	TimeToWaitForStartAiming = 0.5f;
}

void AFurieuxOiseauxPlayerController::OnProjectilePawnFinishRunCallback(AProjectilePawn* Projectile)
{
	if (GetPawn() != Projectile)
	{
		return;
	}
	Projectile->OnFinishRunDelegate.Clear();
	UnPossess();
	if (MainCharacter)
	{
		Possess(MainCharacter);
		MainCharacter->StartAiming();
	}
}
