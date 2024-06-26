// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Interactable/InteractionArgsBase.h"

UInteractionArgsBase::UInteractionArgsBase()
{
}

UInteractionArgsBase::UInteractionArgsBase(AActor* Other)
{
	Interacter = Other;
}

AActor* UInteractionArgsBase::GetInteracter()
{
	return Interacter;
}
