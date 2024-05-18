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

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsGravityAffected;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsGrounded;

private:
	void ApplyGravity();

private:
	const FVector Gravity = { 0, 0, -9.81f };
};
