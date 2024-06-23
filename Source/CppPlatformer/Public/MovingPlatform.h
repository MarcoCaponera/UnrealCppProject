// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/Platforms/PlatformBase.h"
#include "Components/TimelineComponent.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API AMovingPlatform : public APlatformBase
{
	GENERATED_BODY()
public:
	AMovingPlatform();

public:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Checkpoints", Meta = (MakeEditWidget = true))
	FVector EndPoint;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Movement")
	bool bIsOneShot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	bool bAutoActivate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float Duration;

	UFUNCTION()
	void UpdateMove(float Alpha);

	UFUNCTION()
	void FinishedMove();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void StartMove();

	void RevertMove();

protected:
	bool bMove;
	FTimeline MoveTimeline;
	class UCurveFloat* MovementCurve;

private:
	int CurrentCheckPoint = 0;
	bool bPlatformReached;
	FVector StartPoint;
	bool PlayForward;
};
