// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "OrbitalCamera.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API UOrbitalCamera : public UCameraComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotationSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxPitch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MinPitch;


	UPROPERTY(BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly)
	float LastPitchInputDirection;

	UPROPERTY(BlueprintReadOnly)
	bool BlockPitch;


public:
	UOrbitalCamera();

	UFUNCTION(BlueprintCallable)
	void Rotate(FVector2D Value);
};
