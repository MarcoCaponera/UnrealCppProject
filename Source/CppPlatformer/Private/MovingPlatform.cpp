// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	bMove = bAutoActivate;
	StartPoint = GetActorLocation();
	EndPoint = StartPoint + EndPoint;
	PlayForward = false;

	MovementCurve = NewObject<UCurveFloat>(this);
	MovementCurve->FloatCurve.UpdateOrAddKey(0.f, 0.f);
	MovementCurve->FloatCurve.UpdateOrAddKey(Duration, 1.f);

	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("UpdateMove"));

	FOnTimelineEvent FinishedEvent;
	FinishedEvent.BindUFunction(this, FName("FinishedMove"));

	MoveTimeline.AddInterpFloat(MovementCurve, ProgressUpdate);
	MoveTimeline.SetTimelineFinishedFunc(FinishedEvent);

	if (bAutoActivate) 
	{
		StartMove();
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	MoveTimeline.TickTimeline(DeltaTime);
}

void AMovingPlatform::UpdateMove(float Alpha)
{
	UE_LOG(LogTemp, Warning, TEXT("alpha: %f"), Alpha);
	FVector NewLocation = FMath::Lerp(StartPoint, EndPoint, Alpha);
	SetActorLocation(NewLocation);
}

void AMovingPlatform::FinishedMove()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Finished"))
	if (!bIsOneShot)
	{
		if (PlayForward)
		{
			StartMove();
			PlayForward = false;
		}
		else
		{
			RevertMove();
			PlayForward = true;
		}
	}
}

void AMovingPlatform::StartMove()
{
	MoveTimeline.PlayFromStart();
	UE_LOG(LogTemp, Warning, TEXT("Move Started"))
}

void AMovingPlatform::RevertMove()
{
	MoveTimeline.ReverseFromEnd();
}