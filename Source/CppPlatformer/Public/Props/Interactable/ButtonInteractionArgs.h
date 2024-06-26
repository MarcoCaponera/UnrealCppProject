// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/Interactable/InteractionArgsBase.h"
#include "ButtonInteractionArgs.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UButtonInteractionArgs : public UInteractionArgsBase
{
	GENERATED_BODY()

public:
	UButtonInteractionArgs();

	void InitButtonInteractionArgs(AActor* Other);
};
