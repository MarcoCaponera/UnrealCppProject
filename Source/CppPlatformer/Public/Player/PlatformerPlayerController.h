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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Input")
	TSoftObjectPtr<class UInputMappingContext> MappingContext;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Input|Actions")
	class UInputAction* MoveAction;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	virtual void MoveCallback(const FInputActionInstance& Value);
};
