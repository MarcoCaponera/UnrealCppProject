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

	UFUNCTION(BlueprintCallable)
	void Move(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void MovementEndXY();

public:
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


private:
	void ApplyGravity();
	void GroundMove(FVector Direction);
	void AerialMove(FVector Direction);
	void ClampHorVelocity(float Max);
	bool GetGroundNormal(FVector& Normal);

private:
	const FVector Gravity = { 0, 0, -9.81f };
	FVector LastMovementInput;
	bool IsMoving;
};
