// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlatformerGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameSystem/PlatformerSaveGame.h"
#include "GameFramework/SaveGame.h"

void UPlatformerGameInstance::SaveGame()
{
	USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UPlatformerSaveGame::StaticClass());
	if (SaveGame)
	{
		UPlatformerSaveGame* PSaveGame = Cast<UPlatformerSaveGame>(SaveGame);
		if (PSaveGame)
		{
			for (TScriptInterface<ISavable> Item : PlayerSavables)
			{
				PSaveGame->PlayersData.Add(Item->GetPlayerData());
			}
			
			for (TScriptInterface<ISavable> Item : PowerUpSavables)
			{
				PSaveGame->PowerUpsData.Add(Item->GetPowerUpData());
			}

			UGameplayStatics::SaveGameToSlot(PSaveGame, FString("Slot1"), 0);
		}
	}
}

void UPlatformerGameInstance::LoadGame()
{
	USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot(FString("Slot1"), 0);
	if (SaveGame)
	{
		UPlatformerSaveGame* PSaveGame = Cast<UPlatformerSaveGame>(SaveGame);
		if (PSaveGame)
		{
			for (FPlayerSaveGameDataBase Data : PSaveGame->PlayersData)
			{
				for (TScriptInterface<ISavable> Item : PlayerSavables)
				{
					if (Item.GetObject()->GetName() == Data.ActorName)
					{
						Item->RestorePlayerData(Data);
						continue;
					}
				}
			}

			for (FPowerUpSaveGameDataBase Data : PSaveGame->PowerUpsData)
			{
				for (TScriptInterface<ISavable> Item : PowerUpSavables)
				{
					if (Item.GetObject()->GetName() == Data.ActorName)
					{
						Item->RestorePowerUpData(Data);
						continue;
					}
				}
			}
		}
	}
}

void UPlatformerGameInstance::AddSavablePlayer(TScriptInterface<ISavable> Item)
{
	if (Item)
	{
		PlayerSavables.Add(Item);
	}
}

void UPlatformerGameInstance::AddSavablePowerUp(TScriptInterface<ISavable> Item)
{
	if (Item)
	{
		PowerUpSavables.Add(Item);
	}
}
