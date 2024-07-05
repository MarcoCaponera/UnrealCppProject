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
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Checkpoint", Meta = (MakeEditWidget = true))
	FVector EndPoint;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Movement")
	bool bIsOneShot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	bool bAutoActivate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float Duration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float Delay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Instigator", Meta = (MakeEditWidget = true))
	class AButtonActor* MoveInstigator;

	UFUNCTION()
	void UpdateMove(float Alpha);

	UFUNCTION()
	void FinishedMove();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void InitMove();

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// returns true if timer started (delay > 0)
	/// </summary>
	/// <returns></returns>
	bool StartTimerIfDelay();


	void StartMove();

	void RevertMove();

protected:
	bool bMove;
	FTimeline MoveTimeline;

	UPROPERTY()
	class UCurveFloat* MovementCurve;

	UPROPERTY()
	FTimerHandle TimerHandle;

private:
	int CurrentCheckPoint = 0;
	bool bPlatformReached;
	FVector StartPoint;
	bool PlayForward;
};
