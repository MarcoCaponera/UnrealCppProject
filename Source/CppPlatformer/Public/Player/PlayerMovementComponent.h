// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "PlayerMovementComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CPPPLATFORMER_API UPlayerMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction) override;

	UPlayerMovementComponent();

	UFUNCTION(BlueprintCallable)
	void Move(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void MovementEndXY();

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UOrbitalCamera* Camera;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Physics")
	bool bIsGravityAffected;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	bool bIsGrounded;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float MaxWalkMovementSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float MaxAerialMovementSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float Acceleration;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float JumpForce;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
	float CurrentHorSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Rotation")
	float RotationSpeed;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Rotation")
	FRotator TargetRotation;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Rotation")
	FRotator CurrentRotation;

protected:
	void ApplyGravity();
	void GroundMove(FVector Direction, bool bDirectionChange);
	void AerialMove(FVector Direction);
	void ClampHorVelocity(float Max);
	bool GetGroundNormal(FVector& Normal);
	bool DetectGround(FHitResult& Hit);
	void SmoothRotation();
	void HandleRotation();

private:
	const FVector Gravity = { 0, 0, -9.81f };
	FVector LastMovementInput;
	//stores the last velocity change (used to set "SmoothRotationFlag")
	FVector2D CachedHorVelocity;
	bool IsMoving;
	//flag to avoid updating rotation even when unnecessary
	bool SmoothRotationFlag;
};
