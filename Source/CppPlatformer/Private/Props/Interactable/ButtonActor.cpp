// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Interactable/ButtonActor.h"
#include "SaveGameSystem/SaveGameInterface.h"
#include "Components/BoxComponent.h"

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

	UMaterial* Mat = LoadObject<UMaterial>(nullptr, *TriggeredMaterialPah);
	if (Mat)
	{
		TriggeredMaterial = Mat;
	}
}

// Called when the game starts or when spawned
void AButtonActor::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface* MatInterface = Mesh->GetMaterial(0);
	if (MatInterface)
	{
		UMaterial* StartMat = MatInterface->GetMaterial();
		if (StartMat)
		{
			StartingMaterial = StartMat;
		}
	}
	
	ISaveGameInterface* SaveGame = Cast<ISaveGameInterface>(GetGameInstance());
	if (SaveGame)
	{
		SaveGame->AddSavableButton(this);
	}
}

// Called every frame
void AButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonActor::Interact(UInteractionArgsBase* InteractionArgs)
{
	if (bConsumeTrigger)
	{
		if (!bTriggered)
		{
			bTriggered = true;
			Mesh->SetMaterial(0, TriggeredMaterial);
			Activate.Broadcast(this);
		}
		return;
	}
	Activate.Broadcast(this);
}

EInteractionType AButtonActor::GetInteractionType()
{
	return EInteractionType::Button;
}

void AButtonActor::Subscribe(TObjectPtr<UObject> InObject, const FName &FunctionName)
{
	Activate.AddUFunction(InObject, FunctionName);
}

FButtonSaveGameDataBase AButtonActor::GetButtonData()
{
	FButtonSaveGameDataBase Data = FButtonSaveGameDataBase();
	Data.ActorName = GetName();
	Data.bPressed = bTriggered;
	return Data;
}

void AButtonActor::RestoreButtonData(FButtonSaveGameDataBase Data)
{
	if (Data.bPressed != bTriggered)
	{
		if (bTriggered)
		{
			Mesh->SetMaterial(0, StartingMaterial);
		}
		else
		{
			Mesh->SetMaterial(0, TriggeredMaterial);
		}
	}
	else
	{
		if (bTriggered)
		{
			Mesh->SetMaterial(0, TriggeredMaterial);
		}
		else
		{
			Mesh->SetMaterial(0, StartingMaterial);
		}
	}
	bTriggered = Data.bPressed;
}

bool AButtonActor::GetTriggered()
{
	return bTriggered;
}
