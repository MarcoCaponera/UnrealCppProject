// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Interactable/PushableActor.h"
#include "Components/BoxComponent.h"
#include "Props/Interactable/PushInteractionArgs.h"

// Sets default values
APushableActor::APushableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetCollisionProfileName(FName("Interactable"));
	Collider->SetSimulatePhysics(true);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetRootComponent(Collider);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APushableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APushableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APushableActor::Interact(UInteractionArgsBase* Args)
{
	UPushInteractionArgs* PushArgs = Cast<UPushInteractionArgs>(Args);
	FVector Force = PushArgs->GetPushForce() * PushArgs->GetPushDirection().GetSafeNormal();
	Collider->AddForceAtLocation(Force, PushArgs->GetForcePoint());
}

EInteractionType APushableActor::GetInteractionType()
{
	return EInteractionType::Push;
}

