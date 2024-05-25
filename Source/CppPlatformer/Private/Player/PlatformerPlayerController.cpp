// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlatformerPlayerController.h"
#include "Player/PlayerInputActions.h"

void APlatformerPlayerController::OnPossess(APawn* InPawn)
{
	if (InPawn)
	{
		Super::OnPossess(InPawn);
		IPlayerInputActions* Interface = Cast<IPlayerInputActions>(InPawn);
		if (Interface)
		{
			PlayerInputActionsInstance.SetInterface(Interface);
			PlayerInputActionsInstance.SetObject(InPawn);
			return;
		}
	}
	PlayerInputActionsInstance = nullptr;
}

void APlatformerPlayerController::SetupInputComponent()
{
	
}
