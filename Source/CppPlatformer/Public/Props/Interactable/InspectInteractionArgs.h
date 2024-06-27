// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/Interactable/InteractionArgsBase.h"
#include "InspectInteractionArgs.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UInspectInteractionArgs : public UInteractionArgsBase
{
	GENERATED_BODY()
	
public:
	UInspectInteractionArgs();

	void InitInspectInteractionArgs(AActor* Other, class UCameraComponent* Camera, FVector InTargetPosition);

	FVector GetTargetPosition();

	UCameraComponent* GetCamera();

protected:
	FVector TargetPosition;
	class UCameraComponent* CurrentCamera;
};
