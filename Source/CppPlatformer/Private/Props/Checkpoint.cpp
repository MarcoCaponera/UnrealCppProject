// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Checkpoint.h"
#include "Components/BoxComponent.h"
#include "SaveGameSystem/SaveGameInterface.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetGenerateOverlapEvents(true);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlap);
	Collider->SetCollisionProfileName(FName("OnlyPlayer"));
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
	bTriggered = false;
}

void ACheckpoint::Save()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		ISaveGameInterface* SaveGame = Cast<ISaveGameInterface>(GameInstance);
		if (SaveGame)
		{
			SaveGame->SaveGame();
			UE_LOG(LogTemp, Warning, TEXT("SaveCalled"));
		}
	}
}

void ACheckpoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACheckpoint::Save, 0.5f, false, 0.f);
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

