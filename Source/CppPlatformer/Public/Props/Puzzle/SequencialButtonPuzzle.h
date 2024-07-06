// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Props/Puzzle/PuzzleButton.h"
#include "SaveGameSystem/Savable.h"
#include "SequencialButtonPuzzle.generated.h"

UCLASS()
class CPPPLATFORMER_API ASequencialButtonPuzzle : public AActor, public ISavable
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

	UFUNCTION()
	virtual FPuzzleSaveGameDataBase GetPuzzleData() override;

	UFUNCTION()
	virtual void RestorePuzzleData(FPuzzleSaveGameDataBase Data) override;

	virtual void ResetCurrentButton();

	virtual bool CheckSolveCondition();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (MakeEditWidget = true))
	TMap<APuzzleButton*, int> Buttons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (MakeEditWidget = true))
	class AMovingPlatform* Platform;

	FString CorrectMaterialPath = "/Game/MyContent/Materials/M_Green.M_Green";

	const FString CorrectSoundPath = "/Game/MyContent/Sound/CorrectAnswerSound.CorrectAnswerSound";
	const FString WrongSoundPath = "/Game/MyContent/Sound/WrongAnswerSound.WrongAnswerSound";

	USoundWave* CorrectSound;
	USoundWave* WrongSound;

	UPROPERTY()
	UMaterial* CorrectMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int CurrentButton = 0;
};
