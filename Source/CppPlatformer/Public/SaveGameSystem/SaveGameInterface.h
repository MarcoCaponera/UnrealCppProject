// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Savable.h"
#include "SaveGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveGameInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPPPLATFORMER_API ISaveGameInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SaveGame();

	virtual void LoadGame();

	virtual void AddSavablePlayer(TScriptInterface<ISavable> Savable);

	virtual void AddSavablePowerUp(TScriptInterface<ISavable> Savable);

	virtual void AddSavableButton(TScriptInterface<ISavable> Savable);

	virtual void AddSavablePuzzle(TScriptInterface<ISavable> Savable);
};
