// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "Player/PlayerMovementComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Player/OrbitalCamera.h"
#include "Props/Interactable/Interactable.h"
#include "GameFramework/SpringArmComponent.h"
#include "Props/Interactable/ButtonInteractionArgs.h"
#include "Props/Interactable/InteractionArgsBase.h"
#include "Props/Interactable/PushInteractionArgs.h"
#include "Props/Interactable/InspectInteractionArgs.h"
#include "SaveGameSystem/SaveGameInterface.h"
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

	ISaveGameInterface* SaveGame = Cast<ISaveGameInterface>(GetGameInstance());
	if (SaveGame)
	{
		SaveGame->AddSavablePlayer(this);
	}
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

UPlayerMovementComponent* APlayerPawn::GetPlayerMovementComponent() const
{
	return MovementComponent;
}

FPlayerSaveGameDataBase APlayerPawn::GetPlayerData()
{
	FPlayerSaveGameDataBase Data = FPlayerSaveGameDataBase();
	Data.ActorName = GetName();
	Data.PlayerTransform = GetTransform();
	Data.NumJumps = MovementComponent->MaxAerialJumps;
	return Data;
}

void APlayerPawn::RestorePlayerData(FPlayerSaveGameDataBase Data)
{

	SetActorTransform(Data.PlayerTransform);
	MovementComponent->MaxAerialJumps = Data.NumJumps;
}

int APlayerPawn::GetPlayerNumJumps() const
{
	return MovementComponent->MaxAerialJumps;
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

void APlayerPawn::Interact(const FInputActionInstance& Input)
{
	FHitResult Hit;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + GetActorForwardVector() * InteractionRange;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Cyan, false, 1.f, 0, 5);
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), TraceEnd, ECollisionChannel::ECC_GameTraceChannel8))
	{
		IInteractable* IHit = Cast<IInteractable>(Hit.GetActor());
		if (IHit)
		{
			EInteractionType InteractionType = IHit->GetInteractionType();

			switch (InteractionType)
			{
				case EInteractionType::Button:
				{
					UButtonInteractionArgs* ButtonArgs = NewObject<UButtonInteractionArgs>(UButtonInteractionArgs::StaticClass());
					ButtonArgs->InitButtonInteractionArgs(this);
					IHit->Interact(ButtonArgs);
					break;
				}
				case EInteractionType::Push:
				{
					UPushInteractionArgs* PushArgs = NewObject<UPushInteractionArgs>(UPushInteractionArgs::StaticClass());
					PushArgs->InitPushInteractionArgs(this, (TraceEnd - TraceStart).GetSafeNormal(), PushForce, Hit.ImpactPoint);
					IHit->Interact(PushArgs);
					break;
				}
				case EInteractionType::Inspect:
				{
					UInspectInteractionArgs* InspectArgs = NewObject<UInspectInteractionArgs>(UInspectInteractionArgs::StaticClass());
					FVector TargetPos = OrbitalCamera->GetComponentLocation() + OrbitalCamera->GetForwardVector();
					InspectArgs->InitInspectInteractionArgs(this, OrbitalCamera,TargetPos);
					IHit->Interact(InspectArgs);
					break;
				}
			}
		}
	}
}

void APlayerPawn::AddJump()
{	
	MovementComponent->MaxAerialJumps = MovementComponent->MaxAerialJumps + 1;
}

