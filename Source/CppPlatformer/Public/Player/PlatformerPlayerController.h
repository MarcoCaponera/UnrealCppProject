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
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Input|Actions")
	class UInputAction* JumpAction;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Input|Actions")
	class UInputAction* LookAction;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	virtual void MoveStartedCallback(const FInputActionInstance& Value);

	virtual void MoveEndedCallback(const FInputActionInstance& Value);

	virtual void JumpCallback(const FInputActionInstance& Value);

	virtual void LookCallback(const FInputActionInstance& Value);
};
