// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveGameSystem/Savable.h"
#include "PowerUpBase.generated.h"

UCLASS()
class CPPPLATFORMER_API APowerUpBase : public AActor, public ISavable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties 
	APowerUpBase();

	UFUNCTION()
	virtual FPowerUpSaveGameDataBase GetPowerUpData();

	UFUNCTION()
	virtual void RestorePowerUpData(FPowerUpSaveGameDataBase Data);

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UBoxComponent* Collider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void ActivateEffect(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bTaken;
};
