// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Interactable/PushInteractionArgs.h"

UPushInteractionArgs::UPushInteractionArgs()
{

}

void UPushInteractionArgs::InitPushInteractionArgs(AActor* Other, FVector PushDir, float PushFor, FVector PushPoint)
{
	Interacter = Other;
	PushDirection = PushDir;
	PushForce = PushFor;
	ForcePoint = PushPoint;
}

FVector UPushInteractionArgs::GetPushDirection()
{
	return PushDirection;
}

float UPushInteractionArgs::GetPushForce()
{
	return PushForce;
}

FVector UPushInteractionArgs::GetForcePoint()
{
	return ForcePoint;
}