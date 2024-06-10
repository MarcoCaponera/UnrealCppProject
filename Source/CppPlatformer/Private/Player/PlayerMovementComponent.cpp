// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMovementComponent.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/PlayerReferenceGetter.h"
#include "Player/PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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
	}

	//I prefer to detect ground collision with a line trace rather than with collision directly, gives me more control 
	if (DetectGround(Hit))
	{
		Velocity.Z = 0;
		if (!IsMoving)
		{
			Velocity.X = 0;
			Velocity.Y = 0;
		}
	}
	SmoothRotation();
}

UPlayerMovementComponent::UPlayerMovementComponent()
{
	if (GetOwner())
	{
		IPlayerReferenceGetter* PlayerReference = Cast<IPlayerReferenceGetter>(GetOwner());
		if (PlayerReference)
		{
			PlayerGetterReference.SetInterface(PlayerReference);
			PlayerGetterReference.SetObject(GetOwner());
		}
	}
	
}

void UPlayerMovementComponent::MovementEndXY()
{
	IsMoving = false;
	if (bIsGrounded)
	{
		Velocity.X = 0;
		Velocity.Y = 0;
		CurrentHorSpeed = 0;
	}
}

void UPlayerMovementComponent::Move(FVector Direction)
{
	IsMoving = true;
	bool bDirectionChange = LastMovementInput != Direction;
	if (bIsGrounded)
	{
		GroundMove(Direction, bDirectionChange);
	}
	else
	{
		AerialMove(Direction);
	}
	if (bDirectionChange)
	{
		SmoothRotationFlag = true;
	}
	LastMovementInput = Direction;
	TargetRotation = LastMovementInput.Rotation();
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


void UPlayerMovementComponent::GroundMove(FVector Direction, bool bDirectionChange)
{
	FVector Normal; 
	GetGroundNormal(Normal);
	FVector CameraForward = PlayerGetterReference->GetCameraForward();
	FVector CameraRight = PlayerGetterReference->GetCameraRight();
	//UE_LOG(LogTemp, Warning, TEXT("MOVEMENT COMPONENT - X: %f, Y: %f, Z: %f"), CameraForward.X, CameraForward.Y, CameraForward.Z);
	FVector ForwardToUse = -FVector::CrossProduct(Normal, CameraRight);
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + ForwardToUse * 100.f, FColor::Blue, false, -1.f, 0, 5.f);
	FVector RightToUse = FVector::CrossProduct(Normal, CameraForward);
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + RightToUse * 100.f, FColor::Purple, false, -1.f, 0, 5.f);
	FVector VelocityDirection = ForwardToUse * Direction.X + RightToUse * Direction.Y;
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + VelocityDirection * 100.f, FColor::Green, false, -1.f, 0, 5.f);
	VelocityDirection.Normalize();
	if (LastMovementInput != Direction)
	{
		Velocity = VelocityDirection * CurrentHorSpeed;
	}
	CurrentHorSpeed += Acceleration;
	Velocity = VelocityDirection * CurrentHorSpeed;
	ClampHorVelocity(MaxWalkMovementSpeed);
}

void UPlayerMovementComponent::AerialMove(FVector Direction)
{
	Velocity += Direction * Acceleration;
	CurrentHorSpeed += Acceleration;
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
	FVector End = Start - FVector::UpVector * 110;
	DrawDebugLine(GetWorld(), Start, End, FColor::Black, false, -1.f, 0, 5.f);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel2))
	{
		bIsGrounded = true;
	}
	else 
	{
		bIsGrounded = false;
	}
	return bIsGrounded;

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





