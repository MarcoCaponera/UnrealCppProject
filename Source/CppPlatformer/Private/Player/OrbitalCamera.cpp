// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OrbitalCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/PlayerReferenceGetter.h"
#include "Kismet/GameplayStatics.h"

UOrbitalCamera::UOrbitalCamera()
{
    if (GetOwner())
    {
        IPlayerReferenceGetter* Getter = Cast<IPlayerReferenceGetter>(GetOwner());
        if (Getter)
        {
            SpringArm = Getter->GetSpringArm();
            SpringArm->SetUsingAbsoluteRotation(true);
        }
    }
}

void UOrbitalCamera::Rotate(FVector2D Value)
{
    if (LastPitchInputDirection * Value.Y < 0) 
    {
        UE_LOG(LogTemp, Warning, TEXT("Letsgoo"));
    }

    if (LastPitchInputDirection * Value.Y < 0 && BlockPitch == true)
    {
        BlockPitch = false;
        UE_LOG(LogTemp, Warning, TEXT("Pitch Unlocked by Check"));
    }
    LastPitchInputDirection = Value.Y;

    Value = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Diff = FRotator(0, Value.X, 0);

    if (!BlockPitch)
    {
        Diff.Pitch = Value.Y;
    }

    float CurrentPitch = SpringArm->GetRelativeRotation().Pitch;

    if (CurrentPitch > MaxPitch) 
    {
        SpringArm->SetRelativeRotation(FRotator(MaxPitch, SpringArm->GetRelativeRotation().Yaw, SpringArm->GetRelativeRotation().Roll));
        BlockPitch = true;
        UE_LOG(LogTemp, Warning, TEXT("Pitch Blocked by MaxPitch"));
        return;
    }
    else if (CurrentPitch < MinPitch) 
    {
        SpringArm->SetRelativeRotation(FRotator(MinPitch, SpringArm->GetRelativeRotation().Yaw, SpringArm->GetRelativeRotation().Roll));
        BlockPitch = true;
        UE_LOG(LogTemp, Warning, TEXT("Pitch Blocked by MinPitch"));
        return;
    }

    SpringArm->AddRelativeRotation(Diff);
}

