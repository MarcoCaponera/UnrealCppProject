// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Components/TimelineComponent.h"
#include "Curves/RichCurve.h"
#include "Props/Interactable/ButtonActor.h"
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

	FRichCurve RichCurve = FRichCurve();
	RichCurve.AddKey(0.f, 0.f);
	RichCurve.AddKey(Duration, 1.0f);
	MovementCurve = NewObject<UCurveFloat>(this);
	MovementCurve->FloatCurve = RichCurve;

	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("UpdateMove"));

	FOnTimelineEvent FinishedEvent;
	FinishedEvent.BindUFunction(this, FName("FinishedMove"));

	MoveTimeline.AddInterpFloat(MovementCurve, ProgressUpdate);
	MoveTimeline.SetTimelineFinishedFunc(FinishedEvent);

	if (MoveInstigator)
	{
		MoveInstigator->Subscribe(this, FName("InitMove"));
	}

	if (bAutoActivate) 
	{
		InitMove();
	}
}

bool AMovingPlatform::StartTimerIfDelay()
{
	if (Delay > 0)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMovingPlatform::StartMove, Delay, false, Delay);
		return true;
	}
	return false;
}

void AMovingPlatform::InitMove()
{
	if (!StartTimerIfDelay())
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
	FVector NewLocation = FMath::Lerp(StartPoint, EndPoint, Alpha);
	SetActorLocation(NewLocation);
}

void AMovingPlatform::FinishedMove()
{

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
}

void AMovingPlatform::RevertMove()
{
	MoveTimeline.ReverseFromEnd();
}
