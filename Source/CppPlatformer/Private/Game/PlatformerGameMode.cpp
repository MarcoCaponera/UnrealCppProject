// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlatformerGameMode.h"
#include "Player/PlayerPawn.h"

APlatformerGameMode::APlatformerGameMode()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
}