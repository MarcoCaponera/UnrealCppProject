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

public:
	UOrbitalCamera();

	UFUNCTION(BlueprintCallable)
	void Rotate(FVector2D Value);

	UFUNCTION(BlueprintCallable)
	FQuat LookAt(FVector SourcePoint, FVector DestPoint);

protected:
	float CameraDist;
};
