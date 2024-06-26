// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Player/PlayerInputActions.h"
#include "InputMappingContext.h"
#include "Player/PlayerReferenceGetter.h"
#include "Player/PlayerInteractions.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CPPPLATFORMER_API APlayerPawn : public APawn, public IPlayerInputActions, public IPlayerReferenceGetter, public IPlayerInteractions
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
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UOrbitalCamera* OrbitalCamera;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UPlayerMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(BlueprintReadWrite)
	class UArrowComponent* ForwardArrow;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float InteractionRange;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float PushForce;

	const FString SkeletalMeshPath = "/Game/MyContent/Meshes/SKM_PlayerMesh.SKM_PlayerMesh";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual USpringArmComponent* GetSpringArm() const override;

	UFUNCTION(BlueprintCallable)
	virtual UPlayerMovementComponent* GetPlayerMovementComponent() const override;

	virtual void MoveStart(const FInputActionInstance& Value) override;

	virtual void MoveEnd(const FInputActionInstance& Value) override;

	virtual void Jump(const FInputActionInstance& Input) override;

	virtual void Look(const FInputActionInstance& Input) override;

	virtual void Interact(const FInputActionInstance& Input) override;

	virtual void AddJump() override;
};
