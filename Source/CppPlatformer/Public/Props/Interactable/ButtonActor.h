// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ButtonActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FActivationDelegate);
UCLASS()
class CPPPLATFORMER_API AButtonActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UBoxComponent* Collider;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bConsumeTrigger;

	bool bTriggered;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	virtual void Subscribe(TObjectPtr<UObject> InObject, const FName& FunctionName) override;

	FActivationDelegate Activate;
};
