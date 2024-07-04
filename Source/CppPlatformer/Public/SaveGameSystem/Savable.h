// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Savable.generated.h"

USTRUCT(BlueprintType)
struct FSaveGameDataBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString ActorName;
};

USTRUCT(BlueprintType)
struct FPlayerSaveGameDataBase : public FSaveGameDataBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FTransform PlayerTransform;

	UPROPERTY(BlueprintReadWrite)
	int NumJumps;
};

USTRUCT(BlueprintType)
struct FPowerUpSaveGameDataBase : public FSaveGameDataBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FTransform PowerUpTransform;

	UPROPERTY(BlueprintReadWrite)
	bool bTaken;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USavable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPPPLATFORMER_API ISavable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual FPlayerSaveGameDataBase GetPlayerData();

	UFUNCTION()
	virtual void RestorePlayerData(FPlayerSaveGameDataBase Data);

	UFUNCTION()
	virtual FPowerUpSaveGameDataBase GetPowerUpData();

	UFUNCTION()
	virtual void RestorePowerUpData(FPowerUpSaveGameDataBase Data);
};
