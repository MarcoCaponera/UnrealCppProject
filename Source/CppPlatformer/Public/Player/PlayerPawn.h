// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Player/PlayerInputActions.h"
#include "InputMappingContext.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CPPPLATFORMER_API APlayerPawn : public APawn, public IPlayerInputActions
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UOrbitalCamera* OrbitalCamera;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UPlayerMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(BlueprintReadWrite)
	class UArrowComponent* ForwardArrow;



	const FString SkeletalMeshPath = "/Game/MyContent/Meshes/SKM_PlayerMesh.SKM_PlayerMesh";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MoveStart(const FInputActionInstance& Value) override;

	virtual void MoveEnd(const FInputActionInstance& Value) override;

	virtual void Jump(const FInputActionInstance& Input) override;

	virtual void Look(const FInputActionInstance& Input) override;
};
