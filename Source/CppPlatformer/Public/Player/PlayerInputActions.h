// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputAction.h"
#include "PlayerInputActions.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInputActions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPPPLATFORMER_API IPlayerInputActions
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void MoveStart(const FInputActionInstance& InputDirection);

	UFUNCTION()
	virtual void MoveEnd(const FInputActionInstance& InputDirection);

	UFUNCTION()
	virtual void Jump(const FInputActionInstance& Input);

	UFUNCTION()
	virtual void Look(const FInputActionInstance& InputDirection);

	UFUNCTION()
	virtual void Interact(const FInputActionInstance& Input);
};
