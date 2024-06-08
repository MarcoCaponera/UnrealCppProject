// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OrbitalCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

UOrbitalCamera::UOrbitalCamera()
{
    if (GetOwner())
    {
        CameraTransform = GetComponentTransform();
    }
}

void UOrbitalCamera::Rotate(FVector2D Value)
{
    FVector SelfLocation = GetComponentLocation();
    FVector PlayerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation(); 

    Value = Value * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

    FVector NewLocationXY = SelfLocation + FVector(Value.X, Value.Y, 0);
    FVector FromToVector = NewLocationXY - FromToVector;
    FromToVector.Normalize();

    //SetRelativeLocation(FromToVector * CameraDist);

    //SetWorldRotation(LookAt(SelfLocation, PlayerLocation));

    SetWorldLocation(CameraTransform.GetLocation() + GetOwner()->GetActorLocation());
}

FQuat UOrbitalCamera::LookAt(FVector SourcePoint, FVector DestPoint)
{
    FVector forwardVector = DestPoint - SourcePoint;
    forwardVector.Normalize();

    FVector rotAxis = FVector::CrossProduct(FVector::ForwardVector, forwardVector);
    float dot = FVector::DotProduct(FVector::ForwardVector, forwardVector);

    FQuat q;
    q.Z = rotAxis.X;
    q.Y = rotAxis.Y;
    q.Z = rotAxis.Z;
    q.W = dot + 1;
    q.Normalize();

    return q;
}
