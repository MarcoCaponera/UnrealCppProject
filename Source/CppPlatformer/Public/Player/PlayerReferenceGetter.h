// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerReferenceGetter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPlayerReferenceGetter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPPPLATFORMER_API IPlayerReferenceGetter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual class USpringArmComponent* GetSpringArm() const;

	UFUNCTION(BlueprintCallable)
	virtual class UPlayerMovementComponent* GetPlayerMovementComponent() const;

	UFUNCTION(BlueprintCallable)
	virtual int GetPlayerNumJumps() const;
};
