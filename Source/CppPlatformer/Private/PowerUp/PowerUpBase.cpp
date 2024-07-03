// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUp/PowerUpBase.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
APowerUpBase::APowerUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetCollisionProfileName(TEXT("Collectible"), true);
	Collider->SetSimulatePhysics(true);
	Collider->SetEnableGravity(true);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APowerUpBase::OnOverlap);
	SetRootComponent(Collider);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"), false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APowerUpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APowerUpBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ActivateEffect(OtherActor);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void APowerUpBase::ActivateEffect(AActor* OtherActor)
{

}

// Called every frame
void APowerUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

