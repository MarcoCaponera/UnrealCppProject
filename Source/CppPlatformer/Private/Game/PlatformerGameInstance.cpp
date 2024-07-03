// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlatformerGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameSystem/PlatformerSaveGame.h"
#include "SaveGameSystem/SaveGameDataBase.h"
#include "GameFramework/SaveGame.h"

void UPlatformerGameInstance::SaveGame()
{
	USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UPlatformerSaveGame::StaticClass());
	if (SaveGame)
	{
		UPlatformerSaveGame* PSaveGame = Cast<UPlatformerSaveGame>(SaveGame);
		if (PSaveGame)
		{
			for (TScriptInterface<ISavable> Item : Savables)
			{
				PSaveGame->ActorsData.Add(Item->GetData());
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
			for (USaveGameDataBase* Data : PSaveGame->ActorsData)
			{
				for (TScriptInterface<ISavable> Item : Savables)
				{
					if (Item.GetObject()->GetName() == Data->ActorName)
					{
						Item->RestoreData(Data);
						continue;
					}
				}
			}
		}
	}
}

void UPlatformerGameInstance::AddSavable(TScriptInterface<ISavable> Item)
{
	if (Item)
	{
		Savables.Add(Item);
	}
}
