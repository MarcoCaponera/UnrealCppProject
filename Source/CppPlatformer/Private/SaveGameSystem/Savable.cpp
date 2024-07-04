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
