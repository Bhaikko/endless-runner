// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "EndlessRunner/Core/Environment/MasterTile/MasterTile.h"
#include "Components/ArrowComponent.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{

	NextSpawnPointLocation = FVector(0.0f, 0.0f, 0.0f);
	Points = 0;
	PointsMultiplier = 1;
	Coins = 0;
}

void AEndlessRunnerGameMode::BeginPlay() 
{
	for (uint32 i = 1; i <= 10; i++) {
		SpawnTile();
	}	
}

void AEndlessRunnerGameMode::IncreaseScore(int32 ScoreToAdd) 
{
	Points += (ScoreToAdd * PointsMultiplier);
}

void AEndlessRunnerGameMode::IncreaseCoins(int32 CoinsToAdd) 
{
	Coins += CoinsToAdd;
}

void AEndlessRunnerGameMode::SpawnTile() 
{
	if (!TileClass) {
		UE_LOG(LogTemp, Warning, TEXT("No Tile class Specified!!"));
		return;
	}

	AMasterTile* SpawnedTile = GetWorld()->SpawnActor<AMasterTile>(
		TileClass,
		NextSpawnPointLocation,
		FRotator(0.0f, 0.0f, 0.0f)
	);

	NextSpawnPointLocation = SpawnedTile->GetSpawnPoint()->GetComponentLocation();
}
