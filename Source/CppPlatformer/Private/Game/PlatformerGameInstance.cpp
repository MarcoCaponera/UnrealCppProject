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

			for (TScriptInterface<ISavable> Item : ButtonSavables) 
			{
				PSaveGame->ButtonsData.Add(Item->GetButtonData());
			}

			for (TScriptInterface<ISavable> Item : PuzzleSavables)
			{
				PSaveGame->PuzzlesData.Add(Item->GetPuzzleData());
			}

			for (TScriptInterface<ISavable> Item : PlatformSavables)
			{
				PSaveGame->PlatformsData.Add(Item->GetPlatformData());
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

			for (FButtonSaveGameDataBase Data : PSaveGame->ButtonsData)
			{
				for (TScriptInterface<ISavable> Item : ButtonSavables)
				{
					if (Item.GetObject()->GetName() == Data.ActorName)
					{
						Item->RestoreButtonData(Data);
						continue;
					}
				}
			}

			for (FPuzzleSaveGameDataBase Data : PSaveGame->PuzzlesData)
			{
				for (TScriptInterface<ISavable> Item : PuzzleSavables)
				{
					if (Item.GetObject()->GetName() == Data.ActorName)
					{
						Item->RestorePuzzleData(Data);
						continue;
					}
				}
			}

			for (FMovingPlatformSaveGameData Data : PSaveGame->PlatformsData)
			{
				for (TScriptInterface<ISavable> Item : PlatformSavables)
				{
					if (Item.GetObject()->GetName() == Data.ActorName)
					{
						Item->RestorePlatformData(Data);
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
		if (!PlayerSavables.Contains(Item))
		{
			PlayerSavables.Add(Item);
		}
	}
}

void UPlatformerGameInstance::AddSavablePowerUp(TScriptInterface<ISavable> Item)
{
	if (Item)
	{
		if (!PowerUpSavables.Contains(Item))
		{
			PowerUpSavables.Add(Item);
		}
	}
}

void UPlatformerGameInstance::AddSavableButton(TScriptInterface<ISavable> Item)
{
	if (Item)
	{
		if (!ButtonSavables.Contains(Item))
		{
			ButtonSavables.Add(Item);
		}
	}
}

void UPlatformerGameInstance::AddSavablePuzzle(TScriptInterface<ISavable> Item)
{
	if (Item)
	{
		if (!PuzzleSavables.Contains(Item))
		{
			PuzzleSavables.Add(Item);
		}
	}
}

void UPlatformerGameInstance::AddSavablePlatform(TScriptInterface<ISavable> Item)
{
	if (Item)
	{
		if (!PlatformSavables.Contains(Item))
		{
			PlatformSavables.Add(Item);
		}
	}
}
