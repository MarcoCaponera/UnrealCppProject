// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerReferenceGetter.h"

// Add default functionality here for any IPlayerReferenceGetter functions that are not pure virtual.

USpringArmComponent* IPlayerReferenceGetter::GetSpringArm() const
{
	return nullptr;
}

UPlayerMovementComponent* IPlayerReferenceGetter::GetPlayerMovementComponent() const
{
	return nullptr;
}

int IPlayerReferenceGetter::GetPlayerNumJumps() const
{
	return 0;
}
