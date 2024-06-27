// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionArgsBase.h"
#include "Interactable.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Button  UMETA(DisplayName = "Button"),
	Push	UMETA(DisplayName = "Push"),
	Inspect UMETA(DisplayName = "Inspect"),
	None    UMETA(DisplayName = "None")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPPPLATFORMER_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(UInteractionArgsBase* Args);

	virtual EInteractionType GetInteractionType();

	virtual void Subscribe(TObjectPtr<UObject> InObject, const FName& FunctionName);
};
