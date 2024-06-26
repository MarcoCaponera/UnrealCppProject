// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPlayerSaveGame();

public:
	UPROPERTY(BlueprintReadWrite)
	FVector Location;
	UPROPERTY(BlueprintReadWrite)
	int AvailableJumps;
};
