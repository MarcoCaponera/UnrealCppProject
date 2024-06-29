// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Puzzle/SequencialButtonPuzzle.h"
#include "Props/Puzzle/PuzzleButton.h"
#include "Props/Interactable/Interactable.h"

// Sets default values
ASequencialButtonPuzzle::ASequencialButtonPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UMaterial* Mat = LoadObject<UMaterial>(nullptr, *CorrectMaterialPath);
	if (Mat)
	{
		CorrectMaterial = Mat;
	}
}

// Called when the game starts or when spawned
void ASequencialButtonPuzzle::BeginPlay()
{
	Super::BeginPlay();
	if (Buttons.Num() > 0)
	{
		for (TPair<AButtonActor*, int> Elems : Buttons)
		{
			Elems.Key->Subscribe(this, FName("OnButtonPressed"));
		}
	}
}

void ASequencialButtonPuzzle::OnButtonPressed(APuzzleButton* Caller)
{
	if (Caller)
	{
		if (Buttons[Caller] == CurrentButton)
		{
			CurrentButton = CurrentButton + 1;
			if (CurrentButton >= Buttons.Num())
			{
				for (TPair<APuzzleButton*, int> Elems : Buttons)
				{
					Elems.Key->SetMaterial(CorrectMaterial);
				}
			}
			return;

		}
		ResetCurrentButton();
		for (TPair<APuzzleButton*, int> Elems : Buttons)
		{
			Elems.Key->ResetMe();
		}
	}
}

void ASequencialButtonPuzzle::ResetCurrentButton()
{
	CurrentButton = 0;
}

// Called every frame
void ASequencialButtonPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

