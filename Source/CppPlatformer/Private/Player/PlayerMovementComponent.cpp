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
	
	if (bCanApplyFriction && bIsGrounded)
	{
		ApplyFriction();
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
	bCanApplyFriction = true;
}

void UPlayerMovementComponent::Move(FVector Direction)
{
	bCanApplyFriction = false;
	Velocity += Direction * Acceleration;
	UpdatedComponent->SetWorldRotation(Direction.ToOrientationQuat());
}

void UPlayerMovementComponent::Jump()
{
	if (bIsGrounded)
	{
		Velocity = FVector(Velocity.X, Velocity.Y, JumpForce);
		bIsGrounded = false;
	}
}


void UPlayerMovementComponent::ApplyGravity()
{
	Velocity += Gravity;
}

void UPlayerMovementComponent::ApplyFriction()
{
	FVector2D Result = FMath::Lerp(FVector2D(Velocity.X, Velocity.Y), FVector2D::ZeroVector, Friction);
	Velocity = FVector(Result.X, Result.Y, Velocity.Z);
	if (Result.Length() <= 1.f)
	{
		Velocity.X = 0;
		Velocity.Y = 0;
	}
}




