// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/Core/Environment/MasterTile/MasterTile.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	NextSpawnPointLocation = FVector(0.0f, 0.0f, 0.0f);
	Points = 0;
	PointsMultiplier = 1;
	Coins = 0;

	CurrentTiles = ETilesType::RUNNING;
}

void AEndlessRunnerGameMode::BeginPlay() 
{
	for (uint32 i = 1; i <= 10; i++) {
		SpawnTile();
	}	

	FindReferenceOfSaveGameHandler();
}

void AEndlessRunnerGameMode::IncreaseScore(int32 ScoreToAdd) 
{
	Points += (ScoreToAdd * PointsMultiplier);
}

void AEndlessRunnerGameMode::IncreaseCoins(int32 CoinsToAdd) 
{
	Coins += CoinsToAdd;
}

void AEndlessRunnerGameMode::TrySetNewHighScore() 
{
	// SaveGameHandler->TrySetNewHighScore(Points);

	UE_LOG(LogTemp, Warning, TEXT("HighScore: %d"), SaveGameHandler->GetHighScore());
}

void AEndlessRunnerGameMode::FindReferenceOfSaveGameHandler() 
{
	TArray<AActor*> SaveGameHandlers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASaveGameHandler::StaticClass(), SaveGameHandlers);

	if (SaveGameHandlers.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Error Finding Save game"));
	} else {
		SaveGameHandler = Cast<ASaveGameHandler>(SaveGameHandlers[0]);
		UE_LOG(LogTemp, Warning, TEXT("HighScore: %d"), SaveGameHandler->GetHighScore());
	}
}

void AEndlessRunnerGameMode::SpawnTile() 
{
	if (!TileClasses[1]) {
		UE_LOG(LogTemp, Warning, TEXT("No Tile class Specified!!"));
		return;
	}


	AMasterTile* SpawnedTile = GetWorld()->SpawnActor<AMasterTile>(
		TileClasses[1],
		NextSpawnPointLocation,
		FRotator(0.0f, 0.0f, 0.0f)
	);

	NextSpawnPointLocation = SpawnedTile->GetSpawnPoint()->GetComponentLocation();
	NextSpawnPointLocation.X += 300.0f;
}
