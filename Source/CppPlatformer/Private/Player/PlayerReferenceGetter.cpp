// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerReferenceGetter.h"

// Add default functionality here for any IPlayerReferenceGetter functions that are not pure virtual.

FVector IPlayerReferenceGetter::GetCameraRight() const
{
	return FVector::ZeroVector;
}

FVector IPlayerReferenceGetter::GetCameraForward() const
{
	return FVector::ZeroVector;
}


USpringArmComponent* IPlayerReferenceGetter::GetSpringArm() const
{
	return nullptr;
}
