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

	UFUNCTION()
	void MoveX(float Value);

	void MoveY(float Value);

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsGravityAffected;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsGrounded;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float WalkMovementSpeed;


private:
	void ApplyGravity();
	void CheckGroundCollision();

private:
	const FVector Gravity = { 0, 0, -9.81f };
};
