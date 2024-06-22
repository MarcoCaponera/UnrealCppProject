// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp/PowerUpBase.h"
#include "JumpPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class CPPPLATFORMER_API AJumpPowerUp : public APowerUpBase
{
	GENERATED_BODY()
public:
	AJumpPowerUp();

protected:
	virtual void ActivateEffect(AActor* OtherActor) override;

protected:
	const FString MeshPath = "/Game/MyContent/Meshes/JumpPUMesh.JumpPUMesh";
};
