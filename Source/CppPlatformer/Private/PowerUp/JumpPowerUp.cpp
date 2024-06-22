// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUp/JumpPowerUp.h"
#include "Player/PlayerInteractions.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/TextRenderComponent.h"

AJumpPowerUp::AJumpPowerUp()
{
	UStaticMesh* MeshAsset = LoadObject<UStaticMesh>(nullptr, *MeshPath);
	if (MeshAsset)
	{
		Mesh->SetStaticMesh(MeshAsset);
	}
	Mesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	FVector MeshSize = Mesh->Bounds.BoxExtent;
	Mesh->SetRelativeLocation(FVector(0, 0, -MeshSize.Z * Mesh->GetRelativeScale3D().Z));
}

void AJumpPowerUp::ActivateEffect(AActor* OtherActor)
{
	IPlayerInteractions* obj = Cast<IPlayerInteractions>(OtherActor);
	if (obj)
	{
		obj->AddJump();
	}
}
