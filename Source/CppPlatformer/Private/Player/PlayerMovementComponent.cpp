// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMovementComponent.h"

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction)
{
	Super::TickComponent(DeltaTime, TickType, TickFunction);
	if (!bIsGrounded && bIsGravityAffected) 
	{
		ApplyGravity();
	}

	FHitResult Hit;
	SafeMoveUpdatedComponent(Velocity * DeltaTime, FRotator::ZeroRotator, true, Hit);
}

void UPlayerMovementComponent::ApplyGravity()
{
	Velocity += Gravity;
}



