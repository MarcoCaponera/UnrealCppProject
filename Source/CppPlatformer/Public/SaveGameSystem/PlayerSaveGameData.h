// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameSystem/SaveGameDataBase.h"
#include "PlayerSaveGameData.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UPlayerSaveGameData : public USaveGameDataBase
{
	GENERATED_BODY()

public:
	UPlayerSaveGameData();

	UPROPERTY(BlueprintReadwrite)
	FTransform PlayerTransform;

	UPROPERTY(BlueprintReadWrite)
	int NumJumps;
};
