// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameSystem/SaveGameDataBase.h"
#include "PowerUpSaveGameData.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UPowerUpSaveGameData : public USaveGameDataBase
{
	GENERATED_BODY()
	
public:
	UPowerUpSaveGameData();

	UPROPERTY(BlueprintReadWrite)
	bool Taken;
};
