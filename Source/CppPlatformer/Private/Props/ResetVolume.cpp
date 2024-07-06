// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ResetVolume.h"
#include "SaveGameSystem/SaveGameInterface.h"
#include "Components/BoxComponent.h"

// Sets default values
AResetVolume::AResetVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetGenerateOverlapEvents(true);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AResetVolume::OnOverlap);
	Collider->SetCollisionProfileName(FName("OnlyPlayer"));

}

// Called when the game starts or when spawned
void AResetVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void AResetVolume::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		ISaveGameInterface* SaveGame = Cast<ISaveGameInterface>(GameInstance);
		if (SaveGame)
		{
			SaveGame->LoadGame();
			UE_LOG(LogTemp, Warning, TEXT("LoadCalled"));
		}
	}
}

// Called every frame
void AResetVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

