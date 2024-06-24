// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BoxComponent.h"
#include "Props/Interactable/ButtonActor.h"

// Sets default values
AButtonActor::AButtonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetCollisionProfileName(FName("Interactable"));
	SetRootComponent(Collider);
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonActor::Interact()
{
	if (bConsumeTrigger)
	{
		if (!bTriggered)
		{
			Activate.Broadcast();
			bTriggered = true;
		}
		return;
	}
	Activate.Broadcast();
}

void AButtonActor::Subscribe(TObjectPtr<UObject> InObject, const FName &FunctionName)
{
	Activate.AddUFunction(InObject, FunctionName);
}

