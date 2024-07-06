// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveGameSystem/SaveGameInterface.h"
#include "SaveGameSystem/Savable.h"
#include "PlatformerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UPlatformerGameInstance : public UGameInstance, public ISaveGameInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void SaveGame() override;

	UFUNCTION(BlueprintCallable)
	virtual void LoadGame() override;

	UFUNCTION(BlueprintCallable)
	virtual void AddSavablePlayer(TScriptInterface<ISavable> Item) override;

	UFUNCTION(BlueprintCallable)
	virtual void AddSavablePowerUp(TScriptInterface<ISavable> Item) override;

	UFUNCTION(BlueprintCallable)
	virtual void AddSavableButton(TScriptInterface<ISavable> Item) override;

	UFUNCTION(BlueprintCallable)
	virtual void AddSavablePuzzle(TScriptInterface<ISavable> Item) override;

	UFUNCTION(BlueprintCallable)
	virtual void AddSavablePlatform(TScriptInterface<ISavable> Item) override;

private:
	UPROPERTY()
	TArray<TScriptInterface<ISavable>> PlayerSavables;

	UPROPERTY()
	TArray<TScriptInterface<ISavable>> PowerUpSavables;

	UPROPERTY()
	TArray<TScriptInterface<ISavable>> ButtonSavables;

	UPROPERTY()
	TArray<TScriptInterface<ISavable>> PuzzleSavables;

	UPROPERTY()
	TArray<TScriptInterface<ISavable>> PlatformSavables;
};
