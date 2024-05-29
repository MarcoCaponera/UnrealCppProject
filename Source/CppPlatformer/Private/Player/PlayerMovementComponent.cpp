// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMovementComponent.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Kismet/KismetMathLibrary.h"

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
		float HitZ = Hit.ImpactNormal.Z;
		if (HitZ > 0.0f)
		{
			bIsGrounded = true;
			Velocity.Z = 0;
		}
	}

}

void UPlayerMovementComponent::MovementEndXY()
{
	if (bIsGrounded)
	{
		Velocity.X = 0;
		Velocity.Y = 0;
		CurrentSpeed = 0;
	}
}

void UPlayerMovementComponent::Move(FVector Direction)
{
	if (bIsGrounded)
	{
		GroundMove(Direction);
	}
	else
	{
		AerialMove(Direction);
	}
	UpdatedComponent->SetWorldRotation(Direction.ToOrientationQuat());
	LastMovementInput = Direction;
}

void UPlayerMovementComponent::Jump()
{
	if (bIsGrounded)
	{
		Velocity.Z = JumpForce;
		bIsGrounded = false;
	}
}


void UPlayerMovementComponent::ApplyGravity()
{
	Velocity += Gravity;
}


void UPlayerMovementComponent::GroundMove(FVector Direction)
{
	FVector2D VelocityXY = FVector2D(Velocity.X, Velocity.Y);
	if (LastMovementInput != Direction)
	{
		Velocity = Direction * CurrentSpeed;
		VelocityXY = FVector2D(Velocity.X, Velocity.Y);
	}
	Velocity += Direction * Acceleration;
	CurrentSpeed += Acceleration;
	ClampHorVelocity(MaxWalkMovementSpeed);
}

void UPlayerMovementComponent::AerialMove(FVector Direction)
{
	Velocity += Direction * Acceleration;
}

void UPlayerMovementComponent::ClampHorVelocity(float Max)
{
	FVector2D VelocityXY = FVector2D(Velocity.X, Velocity.Y);
	if (VelocityXY.SquaredLength() >= Max * Max)
	{
		VelocityXY.Normalize();
		VelocityXY = VelocityXY * Max;
		Velocity = FVector(VelocityXY.X, VelocityXY.Y, Velocity.Z);
		CurrentSpeed = Max;
	}
}




