// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/Core/Environment/MasterTile/MasterTile.h"
#include "EndlessRunner/Core/Environment/MasterTile/RunningTile/RunningTile.h"
#include "EndlessRunner/Core/Environment/MasterTile/WallRunning/WallRunning.h"

#include "EndlessRunner/Core/Environment/Follower/Follower.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	NextSpawnPointLocation = FVector(0.0f, 0.0f, 0.0f);
	Points = 0;
	PointsMultiplier = 1;
	Coins = 0;
}

void AEndlessRunnerGameMode::BeginPlay() 
{
	// CurrentTiles = EndlessRunnerEnums::ETilesType::GLIDING;
	// CurrentTiles = EndlessRunnerEnums::ETilesType::RUNNING;
	CurrentTiles = EndlessRunnerEnums::ETilesType::RUNNING;

	for (uint32 i = 1; i <= 10; i++) {
		SpawnTile();
	}	

	FindReferenceOfSaveGameHandler();
}

void AEndlessRunnerGameMode::IncreaseScore(int32 ScoreToAdd) 
{
	Points += (ScoreToAdd * PointsMultiplier);

	if (Points % 3 == 0) {
		ChangeTiles();
	}
}

void AEndlessRunnerGameMode::ChangeTiles()
{
	int32 ChangeRandomInteger = FMath::RandRange(1, 3);
	AEndlessRunnerCharacter* RunnerCharacterReference = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (ChangeRandomInteger == 1) {
		CurrentTiles = EndlessRunnerEnums::ETilesType::RUNNING;
	} else if (ChangeRandomInteger == 2) {
		CurrentTiles = EndlessRunnerEnums::ETilesType::GLIDING;

		if (!SpawnedFollower) {
			SpawnedFollower = GetWorld()->SpawnActor<AFollower>(
				FollowerClass,
				RunnerCharacterReference->GetActorLocation() + FVector(-50.0f, -50.0f, -50.0f),
				FRotator(0.0f, -90.0f, 0.0f)
			);
		}
	} else {
		CurrentTiles = EndlessRunnerEnums::ETilesType::WALLRUNNING;
	}
}

void AEndlessRunnerGameMode::DeleteFollower() 
{
	if (SpawnedFollower) {
		SpawnedFollower->StopFollowing();
	}
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

TArray<FVector> AEndlessRunnerGameMode::GetLaneVectors() 
{
	return CurrentSpawnedTile->GetLanes();
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
	if (!TileClasses[0] || !TileClasses[1] || !TileClasses[2]) {
		UE_LOG(LogTemp, Warning, TEXT("No Tile class Specified!!"));
		return;
	}

	switch (CurrentTiles) {
		case EndlessRunnerEnums::ETilesType::RUNNING:
			CurrentSpawnedTile = GetWorld()->SpawnActor<AMasterTile>(
				TileClasses[0],
				NextSpawnPointLocation,
				FRotator(0.0f, 0.0f, 0.0f)
			);

			break;

		case EndlessRunnerEnums::ETilesType::WALLRUNNING:
			CurrentSpawnedTile = GetWorld()->SpawnActor<AMasterTile>(
				TileClasses[1],
				NextSpawnPointLocation,
				FRotator(0.0f, 0.0f, 0.0f)
			);

			break;

		case EndlessRunnerEnums::ETilesType::GLIDING:
			CurrentSpawnedTile = GetWorld()->SpawnActor<AMasterTile>(
				TileClasses[2],
				NextSpawnPointLocation,
				FRotator(0.0f, 0.0f, 0.0f)
			);

			break;

		default:
			break;
	}


	NextSpawnPointLocation = CurrentSpawnedTile->GetSpawnPoint()->GetComponentLocation();
	NextSpawnPointLocation.X += 300.0f;
}
