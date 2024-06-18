// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "Player/PlayerMovementComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Player/OrbitalCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PhysicsCoollider"));
	CapsuleComponent->SetCollisionProfileName(TEXT("Player"), true);
	SetRootComponent(CapsuleComponent);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(CapsuleComponent);
	OrbitalCamera = CreateDefaultSubobject<UOrbitalCamera>(TEXT("OrbitalCamera"));
	OrbitalCamera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	ForwardArrow->SetupAttachment(CapsuleComponent);
	MovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMovementComponent"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleComponent);
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
	if (Mesh)
	{
		SkeletalMesh->SetSkeletalMesh(Mesh);
	}
	SkeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));
	SkeletalMesh->SetRelativeLocation(FVector(0, 0, -CapsuleComponent->GetUnscaledCapsuleHalfHeight()));
	MovementComponent->Camera = OrbitalCamera;
} 

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

USpringArmComponent* APlayerPawn::GetSpringArm() const
{
	return SpringArm;
}

void APlayerPawn::MoveStart(const FInputActionInstance& Input)
{
	FVector2D Value = Input.GetValue().Get<FVector2D>();
	if (Value != FVector2D::ZeroVector)
	{
		MovementComponent->Move(FVector(Value.X, Value.Y, 0));
	}
}

void APlayerPawn::MoveEnd(const FInputActionInstance& Input)
{
	MovementComponent->MovementEndXY();
}

void APlayerPawn::Jump(const FInputActionInstance& Input)
{
	MovementComponent->Jump();
}

void APlayerPawn::Look(const FInputActionInstance& Input)
{
	FVector2D Value = Input.GetValue().Get<FVector2D>();
	float X = Value.X;
	if (Value != FVector2D::ZeroVector)
	{
		OrbitalCamera->Rotate(Value);
	}
}

