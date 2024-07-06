// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSystem/Savable.h"

// Add default functionality here for any ISavable functions that are not pure virtual.

FPlayerSaveGameDataBase ISavable::GetPlayerData()
{
	return FPlayerSaveGameDataBase();
}

void ISavable::RestorePlayerData(FPlayerSaveGameDataBase Data)
{
}

FPowerUpSaveGameDataBase ISavable::GetPowerUpData()
{
	return FPowerUpSaveGameDataBase();
}

void ISavable::RestorePowerUpData(FPowerUpSaveGameDataBase Data)
{
}

FButtonSaveGameDataBase ISavable::GetButtonData()
{
	return FButtonSaveGameDataBase();
}

void ISavable::RestoreButtonData(FButtonSaveGameDataBase Data)
{
}

FPuzzleSaveGameDataBase ISavable::GetPuzzleData()
{
	return FPuzzleSaveGameDataBase();
}

void ISavable::RestorePuzzleData(FPuzzleSaveGameDataBase Data)
{
}

FMovingPlatformSaveGameData ISavable::GetPlatformData()
{
	return FMovingPlatformSaveGameData();
}

void ISavable::RestorePlatformData(FMovingPlatformSaveGameData Data)
{
}
