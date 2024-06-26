// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/Interactable/InteractionArgsBase.h"
#include "PushInteractionArgs.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UPushInteractionArgs : public UInteractionArgsBase
{
	GENERATED_BODY()

public:
	UPushInteractionArgs();

	void InitPushInteractionArgs(AActor* Other, FVector PushDir, float PushFor, FVector PushPoint);

	FVector GetPushDirection();

	float GetPushForce();

	FVector GetForcePoint();

protected:
	FVector PushDirection;
	float PushForce;
	FVector ForcePoint;
};
