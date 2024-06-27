// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Interactable/InspectInteractionArgs.h"
#include "Camera/CameraComponent.h"

UInspectInteractionArgs::UInspectInteractionArgs()
{
}

void UInspectInteractionArgs::InitInspectInteractionArgs(AActor* Other, UCameraComponent* Camera, FVector InTargetPosition)
{
	TargetPosition = InTargetPosition;
	Interacter = Other;
	CurrentCamera = Camera;
}

FVector UInspectInteractionArgs::GetTargetPosition()
{
	return TargetPosition;
}

UCameraComponent* UInspectInteractionArgs::GetCamera()
{
	return CurrentCamera;
}
