// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Props/Puzzle/PuzzleButton.h"
#include "SequencialButtonPuzzle.generated.h"

UCLASS()
class CPPPLATFORMER_API ASequencialButtonPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASequencialButtonPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnButtonPressed(APuzzleButton* Caller);

	virtual void ResetCurrentButton();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (MakeEditWidget = true))
	TMap<APuzzleButton*, int> Buttons;

	FString CorrectMaterialPath = "/Game/MyContent/Materials/M_Green.M_Green";

	UPROPERTY()
	UMaterial* CorrectMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int CurrentButton = 0;
};
