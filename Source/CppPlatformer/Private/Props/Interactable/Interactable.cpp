// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Interactable/Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::Interact(UInteractionArgsBase* InteractionArgs)
{
}

EInteractionType IInteractable::GetInteractionType()
{
	return EInteractionType::None;
}

void IInteractable::Subscribe(TObjectPtr<UObject> InObject, const FName& FunctionName)
{

}
