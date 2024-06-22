// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMovementComponent.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/PlayerReferenceGetter.h"
#include "Player/PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/OrbitalCamera.h"
#include "DrawDebugHelpers.h"



void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction)
{
	Super::TickComponent(DeltaTime, TickType, TickFunction);
	if (!bIsGrounded && bIsGravityAffected) 
	{
		ApplyGravity();
	}
	

	FHitResult Hit;
	if (!SafeMoveUpdatedComponent(Velocity * DeltaTime, CurrentRotation, true, Hit))
	{
		ResolvePenetration(GetPenetrationAdjustment(Hit), Hit, UpdatedComponent->GetComponentRotation());

		if (Hit.Normal.Z >= 0)
		{
			LastGroundNormal = Hit.ImpactNormal;
			bIsGrounded = true;
		}
	} 
	
	if (DetectGround(Hit))
	{
		if (!bIsMoving)
		{
			Velocity.X = 0;
			Velocity.Y = 0;
			CurrentHorSpeed = 0;
		}
		CurrentJump = 0;
	}
	SmoothRotation();
}


UPlayerMovementComponent::UPlayerMovementComponent()
{
	CachedHorVelocity = FVector2D::ZeroVector;
}


void UPlayerMovementComponent::MovementEndXY()
{
	bIsMoving = false;
	if (bIsGrounded)
	{
		Velocity = FVector::ZeroVector;
		CurrentHorSpeed = 0;
	}
}

void UPlayerMovementComponent::Move(FVector Direction)
{
	bIsMoving = true;
	bool bDirectionChange = LastMovementInput != Direction;
	if (bIsGrounded)
	{
		GroundMove(Direction, bDirectionChange);
	}
	else
	{
		AerialMove(Direction);
	}
	LastMovementInput = Direction;
	HandleRotation();
}

void UPlayerMovementComponent::Jump()
{
	if (CanJump())
	{
		Velocity.Z = JumpForce;
		bIsGrounded = false;
		CurrentJump = CurrentJump + 1;
		UE_LOG(LogTemp, Warning, TEXT("CurrentJump: %i"), CurrentJump);
	}
}


void UPlayerMovementComponent::ApplyGravity()
{
	Velocity += Gravity;
}


void UPlayerMovementComponent::GroundMove(FVector Direction, bool bDirectionChange)
{
	FVector Normal; 
	GetGroundNormal(Normal);
	Normal.Normalize();
	FVector CameraForward = Camera->GetForwardVector();
	FVector CameraRight = Camera->GetRightVector();
	CameraForward.Z = 0;
	CameraRight.Z = 0;
	//UE_LOG(LogTemp, Warning, TEXT("MOVEMENT COMPONENT - X: %f, Y: %f, Z: %f"), CameraForward.X, CameraForward.Y, CameraForward.Z);
	FVector ForwardToUse = -FVector::CrossProduct(LastGroundNormal, CameraRight);
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + ForwardToUse * 100.f, FColor::Blue, false, -1.f, 0, 5.f);
	FVector RightToUse = FVector::CrossProduct(LastGroundNormal, CameraForward);
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + RightToUse * 100.f, FColor::Purple, false, -1.f, 0, 5.f);
	FVector VelocityDirection = ForwardToUse * Direction.X + RightToUse * Direction.Y;
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + VelocityDirection * 100.f, FColor::Green, false, -1.f, 0, 5.f);
	VelocityDirection.Normalize();
	if (LastMovementInput != Direction)
	{
		Velocity = VelocityDirection * CurrentHorSpeed;
	}
	CurrentHorSpeed += GroundAcceleration;
	Velocity = VelocityDirection * CurrentHorSpeed;
	ClampHorVelocity(MaxWalkMovementSpeed);
}

void UPlayerMovementComponent::AerialMove(FVector Direction)
{
	FVector CameraForward = Camera->GetForwardVector();
	FVector CameraRight = Camera->GetRightVector();
	CameraForward.Z = 0;
	CameraRight.Z = 0;
	FVector VelocityDirection = CameraForward * Direction.X + CameraRight * Direction.Y;
	VelocityDirection.Normalize();
	Velocity += VelocityDirection * AirAcceleration;
	CurrentHorSpeed += AirAcceleration;
	ClampHorVelocity(MaxAerialMovementSpeed);
}

void UPlayerMovementComponent::ClampHorVelocity(float Max)
{
	FVector2D VelocityXY = FVector2D(Velocity.X, Velocity.Y);
	if (VelocityXY.SquaredLength() >= Max * Max)
	{
		VelocityXY.Normalize();
		VelocityXY = VelocityXY * Max;
		Velocity = FVector(VelocityXY.X, VelocityXY.Y, Velocity.Z);
		CurrentHorSpeed = Max;
	}
}

bool UPlayerMovementComponent::GetGroundNormal(FVector& Normal)
{
	FHitResult Hit;
	if (DetectGround(Hit)) 
	{
		Normal = Hit.Normal;
		return true;
	}
	return false;
}

bool UPlayerMovementComponent::DetectGround(FHitResult& Hit)
{
	FVector Start = UpdatedComponent->GetComponentLocation();
	FVector End = Start - (FVector::UpVector * 110);
	DrawDebugLine(GetWorld(), Start, End, FColor::Black, false, 0.1f, 0, 1);
	FHitResult NewHit;
	if (GetWorld()->LineTraceSingleByChannel(NewHit, Start, End, ECollisionChannel::ECC_GameTraceChannel2))
	{
		return true;
	}
	if (bIsGrounded) 
	{
		Velocity.Z = 0;
	}
	bIsGrounded = false;
	return false;
}

void UPlayerMovementComponent::SmoothRotation()
{
	if (SmoothRotationFlag)
	{
		if (FMath::Acos(FVector::DotProduct(GetOwner()->GetActorForwardVector(), TargetRotation.Vector())) >= 0.1f)
		{
			CurrentRotation = UKismetMathLibrary::RLerp(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds() * RotationSpeed, true);
		}
		else 
		{
			SmoothRotationFlag = false;
		}
	}
}

void UPlayerMovementComponent::HandleRotation()
{
	FVector2D CurrHorVel = FVector2D(Velocity.X, Velocity.Y);
	if (CurrHorVel != CachedHorVelocity)
	{
		SmoothRotationFlag = true;
		CachedHorVelocity = CurrHorVel;
		TargetRotation = FVector(Velocity.X, Velocity.Y, 0).Rotation();
	}
}

bool UPlayerMovementComponent::CanJump()
{
	bool Result = CurrentJump < MaxAerialJumps || bIsGrounded;
	return Result;
}





