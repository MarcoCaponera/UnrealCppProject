// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "Player/PlayerMovementComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PhysicsCoollider"));
	SetRootComponent(CapsuleComponent);
	MovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMovementComponent"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleComponent);
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
	if (Mesh)
	{
		SkeletalMesh->SetSkeletalMesh(Mesh);
	}
	SkeletalMesh->SetRelativeRotation(FRotator(0, 90, 0));
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

