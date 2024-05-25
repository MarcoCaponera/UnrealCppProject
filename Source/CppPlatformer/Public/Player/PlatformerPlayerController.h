// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player/PlayerInputActions.h"
#include "PlatformerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API APlatformerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected: 
	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IPlayerInputActions> PlayerInputActionsInstance;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;
};
