// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractionArgsBase.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UInteractionArgsBase : public UObject
{
	GENERATED_BODY()

public:
	UInteractionArgsBase();

	UInteractionArgsBase(AActor* Other);

	AActor* GetInteracter();

protected:
	AActor* Interacter;
};
