// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Interactable/InspectableActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Props/Interactable/InspectInteractionArgs.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInspectableActor::AInspectableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetCollisionProfileName(FName("Interactable"));
	SetRootComponent(Collider);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(RootComponent);

	USoundWave* SWave = LoadObject<USoundWave>(nullptr, *Lol);
	if (SWave)
	{
		SoundWave = SWave;
	}
}

// Called when the game starts or when spawned
void AInspectableActor::BeginPlay()
{
	Super::BeginPlay();

	HalfHeightExtent = Mesh->Bounds.BoxExtent.Z;
	MaxRange = MaxRange * MaxRange;
}

// Called every frame
void AInspectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsInspecting)
	{
		HandleInspect(DeltaTime);
		if ((Inspector->GetActorLocation() - GetActorLocation()).SquaredLength() >= MaxRange)
		{
			HandleReset();
		}
	}
}

void AInspectableActor::Interact(UInteractionArgsBase* Args)
{
	if (bIsInspecting)
	{
		HandleReset();
	}
	else
	{
		HandleInspectStart(Args);
	}
}

EInteractionType AInspectableActor::GetInteractionType()
{
	return EInteractionType::Inspect;
}

void AInspectableActor::HandleReset()
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Z = NewLocation.Z - HalfHeightExtent;
	Mesh->SetWorldLocation(NewLocation);
	bIsInspecting = false;
}

void AInspectableActor::HandleInspect(float DeltaTime)
{
	FVector NewLocation = CurrentCamera->GetComponentLocation() + CurrentCamera->GetForwardVector() * InspectOffset;
	NewLocation.Z = NewLocation.Z - HalfHeightExtent;
	Mesh->SetWorldLocation(FMath::Lerp(Mesh->GetComponentLocation(), NewLocation, DeltaTime * 25.f));
}

void AInspectableActor::HandleInspectStart(UInteractionArgsBase* Args)
{
	UInspectInteractionArgs* InspectArgs = Cast<UInspectInteractionArgs>(Args);
	CurrentCamera = InspectArgs->GetCamera();
	Inspector = InspectArgs->GetInteracter();
	UGameplayStatics::PlaySound2D(GetWorld(), SoundWave);
	bIsInspecting = true;
}


