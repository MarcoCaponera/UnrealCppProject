// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Puzzle/PuzzleButton.h"

void APuzzleButton::BeginPlay()
{
	bConsumeTrigger = true;

	StartingMaterial = Mesh->GetMaterial(0)->GetMaterial();
}

void APuzzleButton::ResetMe()
{
	Mesh->SetMaterial(0, StartingMaterial);
	bTriggered = false;
}

void APuzzleButton::SetMaterial(UMaterial* Material)
{
	Mesh->SetMaterial(0, Material);
}

