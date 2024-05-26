// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlatformerPlayerController.h"
#include "Player/PlayerInputActions.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlatformerPlayerController::MoveCallback);
		}
	}

	
}

void APlatformerPlayerController::BeginPlay()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (!MappingContext.IsNull())
		{
			Subsystem->AddMappingContext(MappingContext.LoadSynchronous(), 0);
		}
	}
}

void APlatformerPlayerController::MoveCallback(const FInputActionInstance& Value)
{
	PlayerInputActionsInstance->Move(Value);
}
