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
	virtual void AddSavable(TScriptInterface<ISavable> Item) override;

private:
	UPROPERTY()
	TArray<TScriptInterface<ISavable>> Savables;
};
