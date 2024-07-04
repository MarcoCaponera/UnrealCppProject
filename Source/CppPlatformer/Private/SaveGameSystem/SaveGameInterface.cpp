// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSystem/SaveGameInterface.h"

// Add default functionality here for any ISaveGameInterface functions that are not pure virtual.

void ISaveGameInterface::SaveGame()
{
}

void ISaveGameInterface::LoadGame()
{
}

void ISaveGameInterface::AddSavablePlayer(TScriptInterface<ISavable> Savable)
{
}

void ISaveGameInterface::AddSavablePowerUp(TScriptInterface<ISavable> Savable)
{
}