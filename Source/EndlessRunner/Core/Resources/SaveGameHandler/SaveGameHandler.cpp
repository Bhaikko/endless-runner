// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameHandler.h"
#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/Core/Resources/SaveGameState/SaveGameState.h"
#include "EndlessRunner/EndlessRunnerGameMode.h"

// Sets default values
ASaveGameHandler::ASaveGameHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SlotName = "HighScoreSave";
	bNewSave = true;

}

// Called when the game starts or when spawned
void ASaveGameHandler::BeginPlay()
{
	Super::BeginPlay();
	
	FetchSaveGame();
}

// Called every frame
void ASaveGameHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASaveGameHandler::FetchSaveGame() 
{
	class USaveGame* SaveGame;
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0)) {
		SaveGame = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
		bNewSave = false;
	} else {
		SaveGame = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
		bNewSave = true;
	}

	SaveGameState = Cast<USaveGameState>(SaveGame);

	if (!SaveGameState) {
		UE_LOG(LogTemp, Warning, TEXT("Error Fetching Save Game."));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Save game Fetched"));
	}

}

void ASaveGameHandler::TrySetNewHighScore(int32 NewHighScore) 
{
	if (bNewSave) {
		SaveGameState->SetHighScore(NewHighScore);
		UGameplayStatics::SaveGameToSlot(SaveGameState, SlotName, 0);
	} else {
		if (NewHighScore > SaveGameState->GetHighScore()) {
			SaveGameState->SetHighScore(NewHighScore);

			UGameplayStatics::SaveGameToSlot(SaveGameState, SlotName, 0);
		}
	}

}

