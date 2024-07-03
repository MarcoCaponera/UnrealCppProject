// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSystem/Savable.h"

// Add default functionality here for any ISavable functions that are not pure virtual.

USaveGameDataBase* ISavable::GetData()
{
	return nullptr;
}

void ISavable::RestoreData(USaveGameDataBase* Data)
{
}
