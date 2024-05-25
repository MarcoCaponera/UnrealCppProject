// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlatformerGameMode.h"
#include "Player/PlayerPawn.h"
#include "Player/PlatformerPlayerController.h"

APlatformerGameMode::APlatformerGameMode()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = APlatformerPlayerController::StaticClass();
}