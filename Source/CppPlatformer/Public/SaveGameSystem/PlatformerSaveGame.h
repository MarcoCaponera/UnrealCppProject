// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameSystem/Savable.h"
#include "PlatformerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UPlatformerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPlatformerSaveGame();

	UPROPERTY()
	TArray<FPlayerSaveGameDataBase> PlayersData;

	UPROPERTY()
	TArray<FPowerUpSaveGameDataBase> PowerUpsData;

	UPROPERTY()
	TArray<FButtonSaveGameDataBase> ButtonsData;

	UPROPERTY()
	TArray<FPuzzleSaveGameDataBase> PuzzlesData;

	UPROPERTY()
	TArray<FMovingPlatformSaveGameData> PlatformsData;
};
