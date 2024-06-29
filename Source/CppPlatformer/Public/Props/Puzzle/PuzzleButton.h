// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/Interactable/ButtonActor.h"
#include "PuzzleButton.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API APuzzleButton : public AButtonActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void ResetMe();

	void SetMaterial(UMaterial* Material);
};
