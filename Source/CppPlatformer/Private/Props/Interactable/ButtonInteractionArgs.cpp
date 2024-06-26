// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Interactable/ButtonInteractionArgs.h"

UButtonInteractionArgs::UButtonInteractionArgs()
{
}

void UButtonInteractionArgs::InitButtonInteractionArgs(AActor* Other)
{
	Interacter = Other;
}

