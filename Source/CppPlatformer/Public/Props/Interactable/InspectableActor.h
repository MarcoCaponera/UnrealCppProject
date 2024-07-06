// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Props/Interactable/Interactable.h"
#include "InspectableActor.generated.h"

UCLASS()
class CPPPLATFORMER_API AInspectableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInspectableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(UInteractionArgsBase* Args) override;

	virtual EInteractionType GetInteractionType() override;

protected:
	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UBoxComponent* Collider;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxRange;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float InspectOffset;

protected:
	void HandleReset();

	void HandleInspect(float DeltaTime);

	void HandleInspectStart(UInteractionArgsBase* Args);

private:
	bool bIsInspecting;
	float HalfHeightExtent;
	class USoundWave* SoundWave;
	class UCameraComponent* CurrentCamera;
	const FString Lol = "/Game/MyContent/Sound/InspectSound.InspectSound";
	AActor* Inspector;
};
