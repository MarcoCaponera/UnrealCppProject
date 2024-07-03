// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveGameDataBase.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API USaveGameDataBase : public UObject
{
	GENERATED_BODY()

public:
	USaveGameDataBase();

	UPROPERTY(BlueprintReadWrite)
	FString ActorName;
};
