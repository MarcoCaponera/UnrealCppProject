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
	if (!SafeMoveUpdatedComponent(Velocity * DeltaTime, FRotator::ZeroRotator, true, Hit))
	{
		ResolvePenetration(GetPenetrationAdjustment(Hit), Hit, UpdatedComponent->GetComponentRotation());
	}

}

void UPlayerMovementComponent::MoveX(float Value)
{
	FVector MoveDirection = UpdatedComponent->GetForwardVector() * Value * WalkMovementSpeed;
	Velocity += MoveDirection;
}

void UPlayerMovementComponent::ApplyGravity()
{
	Velocity += Gravity;
}

void UPlayerMovementComponent::CheckGroundCollision()
{
	
}



